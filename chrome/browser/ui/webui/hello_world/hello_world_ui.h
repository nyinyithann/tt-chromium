#ifndef CHROMIUM_HELLO_WORLD_H
#define CHROMIUM_HELLO_WORLD_H

#include "content/public/browser/web_ui_controller.h"
#include "content/public/browser/webui_config.h"
#include "chrome/common/webui_url_constants.h"
#include "content/public/common/url_constants.h"

// Forward declaration so that config definition can come before controller.
class HelloWorldUI;

class HelloWorldUIConfig : public content::DefaultWebUIConfig<HelloWorldUI> {
public:
    HelloWorldUIConfig()
            : DefaultWebUIConfig(content::kChromeUIScheme,
                                 chrome::kChromeUIHelloWorldHost) {}
};

class HelloWorldUI : public content::WebUIController {
  public:
    explicit HelloWorldUI(content::WebUI* web_ui);
    ~HelloWorldUI() override;
};

#endif //CHROMIUM_HELLO_WORLD_H
