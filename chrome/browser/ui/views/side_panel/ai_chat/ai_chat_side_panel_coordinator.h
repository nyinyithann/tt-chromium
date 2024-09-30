#ifndef CHROMIUM_AI_CHAT_SIDE_PANEL_COORDINATOR_H
#define CHROMIUM_AI_CHAT_SIDE_PANEL_COORDINATOR_H

#include "chrome/browser/ui/browser_user_data.h"

class Browser;
class SidePanelRegistry;

namespace views {
    class View;
}  // namespace views

class AIChatSidePanelCoordinator
        : public BrowserUserData<AIChatSidePanelCoordinator> {
public:
    explicit AIChatSidePanelCoordinator(Browser* browser);
    ~AIChatSidePanelCoordinator() override;

    void CreateAndRegisterEntry(SidePanelRegistry* global_registry);

private:
    friend class BrowserUserData<AIChatSidePanelCoordinator>;

    std::unique_ptr<views::View> CreateAIChatWebView();

    BROWSER_USER_DATA_KEY_DECL();
};

#endif //CHROMIUM_AI_CHAT_SIDE_PANEL_COORDINATOR_H
