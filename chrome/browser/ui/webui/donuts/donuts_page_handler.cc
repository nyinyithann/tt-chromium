//
// Created by jazz on 10/10/24.
//

#include "donuts_page_handler.h"

DonutsPageHandler::DonutsPageHandler(
        mojo::PendingReceiver<donuts::mojom::PageHandler> receiver,
        mojo::PendingRemote<donuts::mojom::Page> page,
        DonutsUI* donuts_ui)
        : receiver_(this, std::move(receiver)),
          page_(std::move(page)),
          donuts_ui_(donuts_ui){
    LOG(INFO) << "Construct DonutsPageHandler";
}

DonutsPageHandler::~DonutsPageHandler() {
    LOG(INFO) << "Destruct DonutsPageHandler";
}

// Triggered by outside asynchronous event; sends information to the renderer.
void DonutsPageHandler::OnBakingDonutsFinished(uint32_t num_donuts) {
    page_->DonutsBaked(num_donuts);
}

// Triggered by startPilotLight() call in TS.
void DonutsPageHandler::StartPilotLight() {
    LOG(INFO) << "GetOven()->StartPilotLight()";
}

// Triggered by bakeDonuts() call in TS.
void DonutsPageHandler::BakeDonuts(uint32_t num_donuts) {
  LOG(INFO) << "Baking " << num_donuts << " donuts";
}

// Triggered by getNumberOfDonuts() call in TS; sends a response back to the
// renderer.
void DonutsPageHandler::GetNumberOfDonuts(GetNumberOfDonutsCallback callback) {
    LOG(INFO) << "Called GetNumberOfDonuts";
    uint32_t result = 6; // GetOven()->GetNumberOfDonuts();
    std::move(callback).Run(result);
}

void DonutsPageHandler::ShowUI() {
    auto embedder = donuts_ui_->embedder();
    if (embedder) {
        embedder->ShowUI();
    }
}

void DonutsPageHandler::CloseUI() {
    auto embedder = donuts_ui_ ->embedder();
    if (embedder)
        embedder->CloseUI();
}
