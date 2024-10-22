#ifndef CHROMIUM_AI_CHAT_SIDE_PANEL_WEB_VIEW_H
#define CHROMIUM_AI_CHAT_SIDE_PANEL_WEB_VIEW_H

#include "base/functional/callback_forward.h"
#include "base/memory/raw_ptr.h"
#include "chrome/browser/ui/tabs/tab_strip_model_observer.h"
#include "chrome/browser/ui/views/side_panel/side_panel_web_ui_view.h"
#include "chrome/browser/ui/webui/side_panel/chat/chat.mojom.h"
#include "chrome/browser/ui/webui/side_panel/chat/chat_ui.h"
#include "ui/base/metadata/metadata_header_macros.h"
#include "ui/views/controls/webview/webview.h"
#include "ui/views/view.h"

class Browser;

class AIChatSidePanelWebView : public SidePanelWebUIViewT<ChatUI>,
                               public TabStripModelObserver {
  using SidePanelWebUIViewT_ChatUI = SidePanelWebUIViewT<ChatUI>;
  METADATA_HEADER(AIChatSidePanelWebView, SidePanelWebUIViewT_ChatUI)
 public:
  AIChatSidePanelWebView(Browser* browser, base::RepeatingClosure close_cb);
  AIChatSidePanelWebView(const AIChatSidePanelWebView&) = delete;
  AIChatSidePanelWebView& operator=(const AIChatSidePanelWebView&) = delete;
  ~AIChatSidePanelWebView() override;

  // TabStripModelObserver:
  void OnTabStripModelChanged(
      TabStripModel* tab_strip_model,
      const TabStripModelChange& change,
      const TabStripSelectionChange& selection) override;

  void TabChangedAt(content::WebContents* contents,
                    int index,
                    TabChangeType change_type) override;

  void UpdateActiveSiteInfo(content::WebContents* contents);
  void UpdateActiveSiteInfoToActiveTab();

 private:
  const raw_ptr<Browser> browser_;
  base::WeakPtrFactory<AIChatSidePanelWebView> weak_factory_{this};
};
#endif //CHROMIUM_AI_CHAT_SIDE_PANEL_WEB_VIEW_H