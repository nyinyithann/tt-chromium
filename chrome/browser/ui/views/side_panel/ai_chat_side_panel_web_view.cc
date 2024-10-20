#include "ai_chat_side_panel_web_view.h"

#include <memory>
#include "ui/views/view.h"
#include "ui/views/controls/label.h"
#include "ui/views/layout/flex_layout.h"
#include "ui/views/layout/layout_types.h"
#include "chrome/browser/extensions/api/bookmark_manager_private/bookmark_manager_private_api.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/bookmarks/bookmark_utils.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_element_identifiers.h"
#include "chrome/browser/ui/ui_features.h"
#include "chrome/browser/ui/views/frame/browser_view.h"
#include "chrome/common/webui_url_constants.h"
#include "chrome/grit/generated_resources.h"
#include "ui/base/metadata/metadata_impl_macros.h"
#include "ui/views/view_class_properties.h"

AIChatSidePanelWebView::AIChatSidePanelWebView(Browser *browser) : browser_(browser) {
    auto* layout = SetLayoutManager(std::make_unique<views::FlexLayout>());

    // Configure layout properties to center the label both vertically and horizontally
    layout->SetOrientation(views::LayoutOrientation::kVertical) // Stack items vertically
            .SetMainAxisAlignment(views::LayoutAlignment::kCenter) // Align in the center of the main axis (vertical)
            .SetCrossAxisAlignment(views::LayoutAlignment::kCenter); // Align in the center of the cross axis (horizontal)

    // Create a label to add to the layout
    auto* label1 = new views::Label(u"Chat");
    auto* label2 = new views::Label(u"coming soon...");

    // Add the label to the view
    AddChildView(label1);
    AddChildView(label2);
}

AIChatSidePanelWebView::~AIChatSidePanelWebView() = default;
