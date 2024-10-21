import {ChatAppElement} from "./chat_app";
import {html} from '//resources/lit/v3_0/lit.rollup.js';

export function getHtml(this: ChatAppElement) {
    return html`
        <div id="container">
            <div class="top">
            </div>
            <div class="middle"></div>
            <div class="bottom typing-textarea">
                <textarea id="chat-input" spellcheck="false" placeholder="Ask anything..." required></textarea>
                <span id="send-btn" class="material-symbols-rounded">send</span>
            </div>
        </div>`;
}