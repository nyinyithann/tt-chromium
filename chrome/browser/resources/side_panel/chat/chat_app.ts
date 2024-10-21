import './strings.m.js';

import {CrLitElement} from '//resources/lit/v3_0/lit.rollup.js';
import {getCss} from './chat_app.css.js';
import {getHtml} from './chat_app.html.js';
import type {ChatApiProxy} from "./chat_api_proxy.js";
import {ChatApiProxyImpl} from "./chat_api_proxy.js";

export class ChatAppElement extends CrLitElement {
    private chatApiProxy_: ChatApiProxy = ChatApiProxyImpl.getInstance();
    constructor() {
        super();
        setTimeout(() => this.chatApiProxy_.handler.showUI(), 0);
    }
    static get is() {
        return 'chat-app';
    }

    static override get styles() {
        return getCss();
    }

    // override connectedCallback() {
    //     super.connectedCallback();
    //     setTimeout(() => this.chatApiProxy_.handler.showUI(), 0);
    // }
    //
    // override disconnectedCallback() {
    //     super.disconnectedCallback();
    // }

    override render() {
        return getHtml.bind(this)();
    }

}

declare global {
    interface HTMLElementTagNameMap {
        'chat-app': ChatAppElement;
    }
}

customElements.define(ChatAppElement.is, ChatAppElement);