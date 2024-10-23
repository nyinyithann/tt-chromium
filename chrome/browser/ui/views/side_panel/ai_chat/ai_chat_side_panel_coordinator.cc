#include "ai_chat_side_panel_coordinator.h"

#include <memory>

#include "chrome/browser/ui/views/side_panel/ai_chat_side_panel_web_view.h"
#include "base/functional/callback.h"
#include "chrome/app/vector_icons/vector_icons.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/views/frame/browser_view.h"
#include "chrome/browser/ui/views/side_panel/side_panel_entry.h"
#include "chrome/browser/ui/views/side_panel/side_panel_registry.h"
#include "chrome/grit/generated_resources.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/models/image_model.h"
#include "ui/base/ui_base_features.h"
#include "ui/views/vector_icons.h"
#include "chrome/browser/ui/views/toolbar/toolbar_view.h"

AIChatSidePanelCoordinator::AIChatSidePanelCoordinator(Browser* browser)
        : BrowserUserData<AIChatSidePanelCoordinator>(*browser) {}

AIChatSidePanelCoordinator::~AIChatSidePanelCoordinator() = default;

void AIChatSidePanelCoordinator::CreateAndRegisterEntry(SidePanelRegistry* global_registry) {
    global_registry->Register(std::make_unique<SidePanelEntry>(
            SidePanelEntry::Id::kAIChat,
            base::BindRepeating(
                    &AIChatSidePanelCoordinator::CreateAIChatWebView,
                    base::Unretained(this))));
}

std::unique_ptr<views::View>
AIChatSidePanelCoordinator::CreateAIChatWebView() {
    return std::make_unique<AIChatSidePanelWebView>(&GetBrowser(),
                                                    base::RepeatingClosure());
}

void AIChatSidePanelCoordinator::UpdateOpeningPanelId(SidePanelEntryId panel_id) {
    auto* browser = &GetBrowser() ;
    auto* browser_view = BrowserView::GetBrowserViewForBrowser(browser);
    if (browser_view) {
        auto* toolbar = browser_view->toolbar();
        if (panel_id != SidePanelEntry::Id::kAIChat) {
            toolbar->ResetHighlightForAIChatButton();
        } else {
            toolbar->AddHighlightForAIChatButton();
        }
    }
}

void AIChatSidePanelCoordinator::UpdateClosingPanelId(SidePanelEntryId panel_id) {
    auto* browser = &GetBrowser() ;
    auto* browser_view = BrowserView::GetBrowserViewForBrowser(browser);
    if (browser_view && panel_id == SidePanelEntry::Id::kAIChat) {
        auto* toolbar = browser_view->toolbar();
        toolbar->ResetHighlightForAIChatButton();
    }
}

BROWSER_USER_DATA_KEY_IMPL(AIChatSidePanelCoordinator);
