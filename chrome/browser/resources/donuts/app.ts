import './strings.m.js';

import 'chrome://resources/cr_elements/cr_button/cr_button.js';

import {loadTimeData} from 'chrome://resources/js/load_time_data.js';
import {CrLitElement} from '//resources/lit/v3_0/lit.rollup.js';

import {getCss} from './app.css.js';
import {getHtml} from './app.html.js';
import type {ApiProxy} from "./api_proxy.js";
import {ApiProxyImpl} from "./api_proxy.js";

// let numDonutsBaked: number = 0;

// window.onload = function() {
//     // Other page initialization steps go here
//     const proxy = ApiProxyImpl.getInstance();
//     // Tells the browser to start the pilot light.
//     proxy.handler.startPilotLight();
//     // Adds a listener for the asynchronous "donutsBaked" event.
//     proxy.callbackRouter.donutsBaked.addListener(
//         (value: {numDonuts: number}) => {
//             numDonutsBaked += value.numDonuts;
//         });
// };

export class DonutsAppElement extends CrLitElement {

    static get is() {
        return 'donuts-app';
    }

    static override get styles() {
        return getCss();
    }

    override render() {
        return getHtml.bind(this)();
    }

    static override get properties() {
        return {
            message_: {type: String},
        };
    }

    protected message_: string = loadTimeData.getString('message');

    private apiProxy_: ApiProxy =
        ApiProxyImpl.getInstance();
    checkNumberOfDonuts() {
      this.apiProxy_.handler.getNumberOfDonuts().then(
            (value: {numDonuts: number}) => {
                alert('Yay, there are ' + value.numDonuts + ' delicious donuts left!');
            });
    }

    bakeDonuts(numDonuts: number) {
        this.apiProxy_.handler.bakeDonuts(numDonuts);
    }
}

declare global {
    interface HTMLElementTagNameMap {
        'donuts-app': DonutsAppElement;
    }
}

customElements.define(DonutsAppElement.is, DonutsAppElement);
