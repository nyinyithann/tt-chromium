#include "chat_page_handler.h"

ChatPageHandler::ChatPageHandler(
        mojo::PendingReceiver<chat::mojom::PageHandler> receiver,
        mojo::PendingRemote<chat::mojom::Page> page,
        ChatUI* chat_ui)
        : receiver_(this, std::move(receiver)),
          page_(std::move(page)),
          chat_ui_(chat_ui) {
}

ChatPageHandler::~ChatPageHandler() = default;

void ChatPageHandler::ShowUI() {
    auto embedder = chat_ui_->embedder();
    if (embedder) {
        embedder->ShowUI();
    }
}

void ChatPageHandler::CloseUI() {
    auto embedder = chat_ui_->embedder();
    if (embedder)
        embedder->CloseUI();
}