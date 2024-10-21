import {PageCallbackRouter, PageHandlerFactory, PageHandlerRemote} from './chat.mojom-webui.js';
import type {PageHandlerInterface} from './chat.mojom-webui.js';

export interface ChatApiProxy {
    getCallbackRouter(): PageCallbackRouter;
    handler: PageHandlerInterface;
}

let instance: ChatApiProxy|null = null;

export class ChatApiProxyImpl implements ChatApiProxy {
    private readonly callbackRouter: PageCallbackRouter = new PageCallbackRouter();
    handler: PageHandlerRemote = new PageHandlerRemote();

    constructor() {
        this.callbackRouter = new PageCallbackRouter();
        this.handler = new PageHandlerRemote();
        const factory = PageHandlerFactory.getRemote();
        factory.createPageHandler(
            this.callbackRouter.$.bindNewPipeAndPassRemote(),
            this.handler.$.bindNewPipeAndPassReceiver());
    }

    static getInstance(): ChatApiProxy {
        return instance || (instance = new ChatApiProxyImpl());
    }

    static setInstance(proxy: ChatApiProxy) {
        instance = proxy;
    }

    getCallbackRouter() {
        return this.callbackRouter;
    }
}