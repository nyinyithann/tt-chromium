//
// Created by jazz on 10/10/24.
//

#ifndef CHROMIUM_DONUTS_PAGE_HANDLER_H
#define CHROMIUM_DONUTS_PAGE_HANDLER_H

#include "chrome/browser/ui/webui/donuts/donuts.mojom.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "mojo/public/cpp/bindings/remote.h"
#include "chrome/browser/ui/webui/donuts/donuts_ui.h"

class DonutsPageHandler : public donuts::mojom::PageHandler {
 public:
    DonutsPageHandler(
            mojo::PendingReceiver<donuts::mojom::PageHandler> receiver,
            mojo::PendingRemote<donuts::mojom::Page> page,
            DonutsUI* donuts_ui
            );

    DonutsPageHandler(const DonutsPageHandler&) = delete;
    DonutsPageHandler& operator=(const DonutsPageHandler&) = delete;

    ~DonutsPageHandler() override;

    // Triggered by some outside event
    void OnBakingDonutsFinished(uint32_t num_donuts);

    // donuts::mojom::PageHandler:
    void StartPilotLight() override;
    void BakeDonuts(uint32_t num_donuts) override;
    void GetNumberOfDonuts(GetNumberOfDonutsCallback callback) override;
    void ShowUI() override;
    void CloseUI() override;

 private:
    mojo::Receiver<donuts::mojom::PageHandler> receiver_;
    mojo::Remote<donuts::mojom::Page> page_;
    const raw_ptr<DonutsUI> donuts_ui_;
};

#endif //CHROMIUM_DONUTS_PAGE_HANDLER_H
