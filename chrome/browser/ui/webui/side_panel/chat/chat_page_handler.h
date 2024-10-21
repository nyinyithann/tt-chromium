#ifndef CHROMIUM_CHAT_PAGE_HANDLER_H
#define CHROMIUM_CHAT_PAGE_HANDLER_H

#include "chrome/browser/ui/webui/side_panel/chat/chat.mojom.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "mojo/public/cpp/bindings/remote.h"
#include "chat_ui.h"

class ChatPageHandler : public chat::mojom::PageHandler {
public:
    ChatPageHandler(
            mojo::PendingReceiver<chat::mojom::PageHandler> receiver,
            mojo::PendingRemote<chat::mojom::Page> page,
            ChatUI* chat_ui
    );

    ChatPageHandler(const ChatPageHandler&) = delete;
    ChatPageHandler& operator=(const ChatPageHandler&) = delete;

    ~ChatPageHandler() override;

    void ShowUI() override;
    void CloseUI() override;

private:
    mojo::Receiver<chat::mojom::PageHandler> receiver_;
    mojo::Remote<chat::mojom::Page> page_;
    const raw_ptr<ChatUI> chat_ui_;
};
#endif //CHROMIUM_CHAT_PAGE_HANDLER_H
