#ifndef CHROMIUM_DONUTS_UI_H
#define CHROMIUM_DONUTS_UI_H


#include "chrome/browser/ui/webui/donuts/donuts.mojom.h"
#include "content/public/browser/web_ui_controller.h"
#include "content/public/browser/webui_config.h"
#include "chrome/common/webui_url_constants.h"
#include "content/public/common/url_constants.h"
#include "ui/webui/mojo_web_ui_controller.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/pending_remote.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "chrome/browser/ui/webui/top_chrome/top_chrome_web_ui_controller.h"
#include "chrome/browser/ui/webui/top_chrome/top_chrome_webui_config.h"

// Forward declaration so that config definition can come before controller.
class DonutsUI;

class DonutsUIConfig : public DefaultTopChromeWebUIConfig<DonutsUI> {
public:
    DonutsUIConfig()
            : DefaultTopChromeWebUIConfig(content::kChromeUIScheme,
                                 chrome::kChromeUIDonutsHost) {}
};

class DonutsPageHandler;

class DonutsUI : public TopChromeWebUIController,
                 public donuts::mojom::PageHandlerFactory {
public:
    explicit DonutsUI(content::WebUI* web_ui);

    DonutsUI(const DonutsUI&) = delete;
    DonutsUI& operator=(const DonutsUI&) = delete;

    ~DonutsUI() override;

    // Instantiates the implementor of the mojom::PageHandlerFactory mojo
    // interface passing the pending receiver that will be internally bound.
    void BindInterface(
            mojo::PendingReceiver<donuts::mojom::PageHandlerFactory> receiver);

    static constexpr std::string GetWebUIName() { return "AIChatSidePanel"; }

private:
    // donuts::mojom::PageHandlerFactory:
    void CreatePageHandler(
            mojo::PendingRemote<donuts::mojom::Page> page,
            mojo::PendingReceiver<donuts::mojom::PageHandler> receiver) override;

    std::unique_ptr<DonutsPageHandler> page_handler_;

    mojo::Receiver<donuts::mojom::PageHandlerFactory> page_factory_receiver_{
            this};

    WEB_UI_CONTROLLER_TYPE_DECL();
};
#endif //CHROMIUM_DONUTS_UI_H
