#include "chrome/browser/ui/webui/donuts/donuts_ui.h"
#include "chrome/browser/ui/webui/donuts/donuts_page_handler.h"
#include "chrome/browser/ui/webui/webui_util.h"
#include "chrome/common/webui_url_constants.h"
#include "content/public/common/url_constants.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_ui.h"
#include "content/public/browser/web_ui_data_source.h"
#include "content/public/browser/web_ui_controller.h"
#include "content/public/browser/webui_config.h"
#include "chrome/grit/donuts_resources.h"
#include "chrome/grit/donuts_resources_map.h"
#include "ui/webui/mojo_web_ui_controller.h"
#include "chrome/browser/profiles/profile.h"

#pragma allow_unsafe_buffers

//DonutsUI::DonutsUI(content::WebUI* web_ui)
//    : content::WebUIController(web_ui) {
//    content::WebUIDataSource* source =
//            content::WebUIDataSource::CreateAndAdd(
//                    web_ui->GetWebContents()->GetBrowserContext(),
//                    chrome::kChromeUIDonutsHost);
//
////    Profile* const profile = Profile::FromWebUI(web_ui);
////    content::WebUIDataSource* source = content::WebUIDataSource::CreateAndAdd(
////            profile, chrome::kChromeUIDonutsURL);
////   fill placeholders in all resources - html, ts
//    webui::SetupWebUIDataSource(
//            source,
//            base::make_span(kDonutsResources, kDonutsResourcesSize),
//            IDR_DONUTS_DONUTS_HTML);
//
//   source->AddString("message", "Chat");
//
//   // only fill placeholder in html if use AddResourcePath alone
//    source->AddString("mmmDonuts", "Mmm, Taktak!");
//   // source->AddResourcePath("", IDR_DONUTS_DONUTS_HTML);
//}
DonutsUI::DonutsUI(content::WebUI* web_ui)
    : TopChromeWebUIController(web_ui) {
//    content::WebUIDataSource* source =
//            content::WebUIDataSource::CreateAndAdd(
//                    web_ui->GetWebContents()->GetBrowserContext(),
//                    chrome::kChromeUIDonutsHost);

    Profile* const profile = Profile::FromWebUI(web_ui);
    content::WebUIDataSource* source = content::WebUIDataSource::CreateAndAdd(
            profile, chrome::kChromeUIDonutsHost);
//   fill placeholders in all resources - html, ts
    webui::SetupWebUIDataSource(
            source,
            base::make_span(kDonutsResources, kDonutsResourcesSize),
            IDR_DONUTS_DONUTS_HTML);

   source->AddString("message", "testing...");

   // only fill placeholder in html if use AddResourcePath alone
    source->AddString("mmmDonuts", "Mojom!");
   // source->AddResourcePath("", IDR_DONUTS_DONUTS_HTML);

   // this should be added if call internal resources via xml http
    source->OverrideContentSecurityPolicy(
            network::mojom::CSPDirectiveName::ConnectSrc,
            "connect-src *;");
}

//
DonutsUI::~DonutsUI() = default;

WEB_UI_CONTROLLER_TYPE_IMPL(DonutsUI)

void DonutsUI::BindInterface(
        mojo::PendingReceiver<donuts::mojom::PageHandlerFactory> receiver) {
    page_factory_receiver_.reset();
    page_factory_receiver_.Bind(std::move(receiver));
}

void DonutsUI::CreatePageHandler(
        mojo::PendingRemote<donuts::mojom::Page> page,
        mojo::PendingReceiver<donuts::mojom::PageHandler> receiver) {
    DCHECK(page);
    page_handler_ = std::make_unique<DonutsPageHandler>(
            std::move(receiver), std::move(page), this);
}