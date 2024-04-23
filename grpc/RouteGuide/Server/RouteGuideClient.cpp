//
// Created by tuantq3 on 22/04/2024.
//

#include "RouteGuideClient.h"

#include "Helper.h"

#include <grpcpp/channel.h>
#include <random>
#include <thread>
RouteGuideClient::RouteGuideClient(std::shared_ptr<grpc::Channel> channel, const std::string &db) : stub_(routeguide::RouteGuide::NewStub(channel)) {
    Helper::ParseDB(db, &features_);
}
void RouteGuideClient::GetFeature() {
    routeguide::Point point;
    routeguide::Feature feature;
    point = MakePoint(409146138, -746188906);
    GetOneFeature(point, &feature);
    point = MakePoint(0, 0);
    GetOneFeature(point, &feature);
}
void RouteGuideClient::ListFeatures() {
    routeguide::Rectangle rect;
    routeguide::Feature feature;
    grpc::ClientContext context;

    rect.mutable_lo()->set_latitude(400000000);
    rect.mutable_lo()->set_longitude(-750000000);
    rect.mutable_hi()->set_latitude(420000000);
    rect.mutable_hi()->set_longitude(-730000000);

    std::cout << "Looking for features between 40, -75 and 42, -73"
              << std::endl;

    std::unique_ptr<grpc::ClientReader<routeguide::Feature>> reader(
            stub_->ListFeatures(&context, rect));
    while (reader->Read(&feature)) {
        std::cout << "Found feature called " << feature.name() << " at "
                  << feature.location().latitude() / kCoordFactor_ << ", "
                  << feature.location().longitude() / kCoordFactor_ << std::endl;
    }
    grpc::Status status = reader->Finish();
    if (status.ok()) {
        std::cout << "ListFeatures rpc succeeded." << std::endl;
    } else {
        std::cout << "ListFeatures rpc failed." << std::endl;
    }
}
void RouteGuideClient::RecordRoute() {
    routeguide::Point point;
    routeguide::RouteSummary stats;
    grpc::ClientContext context;
    const int kPoints = 10;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> feature_distribution(
            0, features_.size() - 1);
    std::uniform_int_distribution<int> delay_distribution(500, 1500);

    std::unique_ptr<grpc::ClientWriter<routeguide::Point>> writer(
            stub_->RecordRoute(&context, &stats));
    for (int i = 0; i < kPoints; i++) {
        const routeguide::Feature &f = features_[feature_distribution(generator)];
        std::cout << "Visiting point " << f.location().latitude() / kCoordFactor_
                  << ", " << f.location().longitude() / kCoordFactor_
                  << std::endl;
        if (!writer->Write(f.location())) {
            // Broken stream.
            break;
        }
        std::this_thread::sleep_for(
                std::chrono::milliseconds(delay_distribution(generator)));
    }
    writer->WritesDone();
    grpc::Status status = writer->Finish();
    if (status.ok()) {
        std::cout << "Finished trip with " << stats.point_count() << " points\n"
                  << "Passed " << stats.feature_count() << " features\n"
                  << "Travelled " << stats.distance() << " meters\n"
                  << "It took " << stats.elapsed_time() << " seconds"
                  << std::endl;
    } else {
        std::cout << "RecordRoute rpc failed." << std::endl;
    }
}
void RouteGuideClient::RouteChat() {
    grpc::ClientContext clientContext;
    // use share_ptr for accessing between read and write threads concurrently
    std::shared_ptr<grpc::ClientReaderWriter<routeguide::RouteNote, routeguide::RouteNote>> stream{stub_->RouteChat(&clientContext)};
    std::thread writerThread{[stream]() {
        std::vector<routeguide::RouteNote> notes{
                MakeRouteNote("First msg", 0, 0),
                MakeRouteNote("Second msg", 0, 1),
                MakeRouteNote("Third msg", 1, 0),
                MakeRouteNote("Fourth msg", 0, 0),
        };
        for (const routeguide::RouteNote &note: notes) {
            std::cout << "Sending message " << note.message() << " at "
                      << note.location().latitude() << ", "
                      << note.location().longitude() << std::endl;
            stream->Write(note);
        }
        // call WritesDone() on the stream to let gRPC know that we’ve finished writing
        stream->WritesDone();
    }};

    routeguide::RouteNote serverNote;
    while (stream->Read(&serverNote)) {
        std::cout << "Got message " << serverNote.message() << " at "
                << serverNote.location().latitude() << ", "
                << serverNote.location().longitude() << std::endl;
    }

    writerThread.join();
    // finish both read and write stream and get
    // then Finish() to complete the call and get our RPC status
    grpc::Status status = stream->Finish();
    if (!status.ok()) {
        std::cout << "RouteChat rpc failed." << std::endl;
    }
}
routeguide::Point RouteGuideClient::MakePoint(long latitude, long longitude) {
    routeguide::Point point;
    point.set_latitude(latitude);
    point.set_longitude(longitude);
    return point;
}
routeguide::Feature RouteGuideClient::MakeFeature(const std::string &name, long latitude, long longitude) {
    routeguide::Feature f;
    f.set_name(name);
    f.mutable_location()->CopyFrom(MakePoint(latitude, longitude));
    return f;
}
routeguide::RouteNote RouteGuideClient::MakeRouteNote(const std::string &message, long latitude, long longitude) {
    routeguide::RouteNote n;
    n.set_message(message);
    n.mutable_location()->CopyFrom(MakePoint(latitude, longitude));
    return n;
}
bool RouteGuideClient::GetOneFeature(const routeguide::Point &point, routeguide::Feature *feature) {
    // create ClientContext per call - cannot reuse this object between calls
    // we can use this obect to set RPC configuration on this object
    grpc::ClientContext clientContext;// that means default setting
    grpc::Status status = stub_->GetFeature(&clientContext, point, feature);
    if (!status.ok()) {
        std::cout << "GetFeature rpc failed." << std::endl;
        return false;
    }
    if (!feature->has_location()) {
        std::cout << "Server returns incomplete feature." << std::endl;
        return false;
    }
    if (feature->name().empty()) {
        std::cout << "Found no feature at "
                  << feature->location().latitude() / kCoordFactor_ << ", "
                  << feature->location().longitude() / kCoordFactor_ << std::endl;
    } else {
        std::cout << "Found feature called " << feature->name() << " at "
                  << feature->location().latitude() / kCoordFactor_ << ", "
                  << feature->location().longitude() / kCoordFactor_ << std::endl;
    }
    return true;
}