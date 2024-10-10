import {PageCallbackRouter, PageHandlerFactory, PageHandlerRemote} from './donuts.mojom-webui.js';
import type {PageHandlerInterface} from './donuts.mojom-webui.js';

// Exporting the interface helps when creating a TestBrowserProxy wrapper.
export interface ApiProxy {
    getCallbackRouter(): PageCallbackRouter;
    handler: PageHandlerInterface;
}

let instance: ApiProxy|null = null;

export class ApiProxyImpl implements ApiProxy {
    private readonly callbackRouter: PageCallbackRouter = new PageCallbackRouter();
    handler: PageHandlerRemote = new PageHandlerRemote();

    constructor() {
        this.callbackRouter = new PageCallbackRouter();
        this.handler = new PageHandlerRemote();
        const factory = PageHandlerFactory.getRemote();
        factory.createPageHandler(
            this.callbackRouter.$.bindNewPipeAndPassRemote(),
            this.handler.$.bindNewPipeAndPassReceiver());
        // PageHandlerFactory.getRemote().createPageHandler(
        //     this.callbackRouter.$.bindNewPipeAndPassRemote(),
        //     (this.handler as PageHandlerRemote).$.bindNewPipeAndPassReceiver());
    }

    static getInstance(): ApiProxy {
        return instance || (instance = new ApiProxyImpl());
    }

    static setInstance(proxy: ApiProxy) {
        instance = proxy;
    }

    getCallbackRouter() {
        return this.callbackRouter;
    }
}


// export class ApiProxyImpl implements ApiProxy {
//     callbackRouter: PageCallbackRouter;
//     handler: PageHandlerInterface;
//
//     private constructor() {
//         this.callbackRouter = new PageCallbackRouter();
//         this.handler = new PageHandlerRemote();
//         PageHandlerFactory.getRemote().createPageHandler(
//             this.callbackRouter.$.bindNewPipeAndPassRemote(),
//             (this.handler as PageHandlerRemote).$.bindNewPipeAndPassReceiver());
//     }
//
//     static getInstance(): ApiProxy {
//         return instance || (instance = new ApiProxyImpl());
//     }
//
//     static setInstance(proxy: ApiProxy) {
//         instance = proxy;
//     }
// }
//
// let instance: ApiProxy|null = null;
