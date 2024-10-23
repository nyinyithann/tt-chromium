#include "chat_page_handler.h"

#include <string>

#include "base/strings/string_util.h"
#include "base/strings/utf_string_conversions.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_ui.h"
#include "url/gurl.h"

ChatPageHandler::ChatPageHandler(
    mojo::PendingReceiver<chat::mojom::PageHandler> receiver,
    mojo::PendingRemote<chat::mojom::Page> page,
    ChatUI* chat_ui,
    content::WebUI* web_ui)
    : receiver_(this, std::move(receiver)),
      page_(std::move(page)),
      chat_ui_(chat_ui),
      web_ui_(web_ui),
      web_contents_(web_ui->GetWebContents()) {}

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

void ChatPageHandler::SetSiteInfo(chat::mojom::SiteInfoPtr site_info) {
  if (page_.is_bound()) {
    page_->OnSiteInfoChanged(std::move(site_info));
  }
}

void ChatPageHandler::GetSiteInfo(GetSiteInfoCallback callback) {
  auto title = base::UTF16ToUTF8(web_contents_->GetTitle());
  std::string url;
  const GURL gurl = web_contents_->GetLastCommittedURL();
  if (gurl.SchemeIsHTTPOrHTTPS()) {
    url = gurl.spec();
  }
  chat::mojom::SiteInfoPtr site_info = chat::mojom::SiteInfo::New();
  site_info->title = title;
  site_info->url = url;
  std::move(callback).Run(site_info.Clone());
}
