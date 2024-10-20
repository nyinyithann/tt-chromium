#ifndef CHROMIUM_AI_CHAT_SIDE_PANEL_WEB_VIEW_H
#define CHROMIUM_AI_CHAT_SIDE_PANEL_WEB_VIEW_H

#include "ui/views/view.h"
#include "base/functional/callback_forward.h"
#include "base/memory/raw_ptr.h"
#include "chrome/browser/ui/tabs/tab_strip_model_observer.h"
#include "chrome/browser/ui/views/side_panel/side_panel_web_ui_view.h"
#include "chrome/browser/ui/webui/side_panel/reading_list/reading_list_ui.h"
#include "ui/base/metadata/metadata_header_macros.h"
#include "ui/views/controls/webview/webview.h"

class Browser;

class AIChatSidePanelWebView : public views::View {
    public:
        AIChatSidePanelWebView(Browser* browser);
        AIChatSidePanelWebView(const AIChatSidePanelWebView&) = delete;
        AIChatSidePanelWebView& operator=(const AIChatSidePanelWebView&) =
        delete;
        ~AIChatSidePanelWebView() override;

    private:
        const raw_ptr<Browser> browser_;
        base::WeakPtrFactory<AIChatSidePanelWebView> weak_factory_{this};
};
#endif //CHROMIUM_AI_CHAT_SIDE_PANEL_WEB_VIEW_H