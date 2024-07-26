//
// Created by tuantq3 on 24/07/2024.
//

#ifndef ROUTEGUIDEWRITEREACTOR_H
#define ROUTEGUIDEWRITEREACTOR_H
#include "../gen-cpp/route_guide.grpc.pb.h"
#include "../gen-cpp/route_guide.pb.h"

/**
 * @brief With grpc::ServerWriteReactor, we should implement OnWriteDone(), onDone() and onCancel()
 */
class RouteGuideWriteReactor : public grpc::ServerWriteReactor<routeguide::Feature> {
public:
    /**
     * @brief provide the reactor in response to the started RPC.
     * @param rectangle
     * @param features
     */
    explicit RouteGuideWriteReactor(const routeguide::Rectangle *rectangle, const std::vector<routeguide::Feature>& features);
    /**
     * @brief reacts to a write completion. If it was done successfully -> ProcessNextWrite() and we
     * will call Finish() to finish the call
     * @param isOk
     */
    void OnWriteDone(bool isOk) override;
    /**
     * @brief do the final clean up in this function
     */
    void OnDone() override;
    void OnCancel() override;
private:
    /**
     * @brief our main logic handler - if it's a blocking task or heavy calculation , you should do it in another thread
     */
    void ProcessNextWrite();
    //
    const long left_;
    const long right_;
    const long top_;
    const long bottom_;
    const std::vector<routeguide::Feature>& list_features_;
    std::vector<routeguide::Feature>::const_iterator next_feature_iter_;
};


#endif//ROUTEGUIDEWRITEREACTOR_H
