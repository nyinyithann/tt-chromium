import {PageCallbackRouter, PageHandlerFactory, PageHandlerRemote, SiteInfo}
    from "./chat.mojom-webui.js";

export interface ChatApiProxy {
    getSiteInfo():Promise<{siteInfo: SiteInfo}>
    showUI(): void;
    closeUI(): void;
    getCallbackRouter(): PageCallbackRouter;
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

    showUI() {
        this.handler.showUI();
    }

    closeUI(){
        this.handler.closeUI();
    }

    getSiteInfo() {
      return this.handler.getSiteInfo();
    }
}