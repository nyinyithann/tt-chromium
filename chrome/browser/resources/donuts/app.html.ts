import {html} from '//resources/lit/v3_0/lit.rollup.js';
import type {DonutsAppElement} from './app.js';

export function getHtml(this: DonutsAppElement) {
    return html`
        <div id="container">
            <div class="top">
                <div class="welcome">
                    <p>Hi there! Yep, I'm your AI powered assistant. I can understand and generate text.</p>
                </div>
            </div>
            <div class="middle"></div>

            <div class="bottom typing-textarea">
                <textarea id="chat-input" spellcheck="false" placeholder="Ask anything..." required></textarea>
                <span id="send-btn" class="material-symbols-rounded">send</span>
            </div>
        </div>`;
}
