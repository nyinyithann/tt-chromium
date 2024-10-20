#include "ai_chat_side_panel_web_view.h"

#include <memory>
#include "ui/views/view.h"
#include "ui/views/controls/label.h"
#include "ui/views/layout/flex_layout.h"
#include "ui/views/layout/fill_layout.h"
#include "ui/views/layout/layout_types.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_element_identifiers.h"
#include "chrome/browser/ui/ui_features.h"
#include "chrome/browser/ui/views/frame/browser_view.h"
#include "chrome/common/webui_url_constants.h"
#include "chrome/grit/generated_resources.h"
#include "ui/base/metadata/metadata_impl_macros.h"
#include "ui/views/view_class_properties.h"
#include "ui/views/controls/webview/webview.h"
#include "url/gurl.h"

using SidePanelWebUIViewT_ChatUI = SidePanelWebUIViewT<ChatUI>;
BEGIN_TEMPLATE_METADATA(SidePanelWebUIViewT_ChatUI, SidePanelWebUIViewT)
END_METADATA

AIChatSidePanelWebView::AIChatSidePanelWebView(
        Browser *browser,
        base::RepeatingClosure close_cb)
        : SidePanelWebUIViewT(
        base::BindRepeating(
                &AIChatSidePanelWebView::UpdateActiveURLToActiveTab,
                base::Unretained(this)),
        close_cb,
        std::make_unique<WebUIContentsWrapperT<ChatUI>>(
                GURL(chrome::kChromeUIChatURL),
                browser->profile(),
                IDS_AI_CHAT_TITLE,
                /*esc_closes_ui=*/false)),
          browser_(browser) {

    SetProperty(views::kElementIdentifierKey,
                kChatSidePanelWebViewElementId);
}

void AIChatSidePanelWebView::UpdateActiveURLToActiveTab() {
    LOG(INFO) << "To get current url of the tab";
}

AIChatSidePanelWebView::~AIChatSidePanelWebView() = default;

BEGIN_METADATA(AIChatSidePanelWebView)
END_METADATA