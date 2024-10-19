import './strings.m.js';

import 'chrome://resources/cr_elements/cr_button/cr_button.js';

//import {loadTimeData} from 'chrome://resources/js/load_time_data.js';
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
    private apiProxy_: ApiProxy =
        ApiProxyImpl.getInstance();

    constructor() {
        super();
        setTimeout(() => this.apiProxy_.handler.showUI(),0);
    }
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

    //protected message_: string = loadTimeData.getString('message');

    checkNumberOfDonuts() {
      this.apiProxy_.handler.getNumberOfDonuts().then(
            (value: {numDonuts: number}) => {
                alert('Yay, there are ' + value.numDonuts + ' delicious donuts left!');
            });
    }

    bakeDonuts(numDonuts: number) {
        this.apiProxy_.handler.bakeDonuts(numDonuts);
    }

    addMock() {
        const c = document.querySelector("donuts-app")?.shadowRoot?.querySelector("#mock");
        const p = document.createElement("p");
        p.textContent = "test";
        c?.appendChild(p);
    }

    // this will not work due to CSP - content security policy
    // need to use C++ via mojo
    async getJson() {
        const container = document.querySelector("donuts-app")?.shadowRoot?.querySelector("#mock");
        const API_URL = "https://get.geojs.io/v0/ip/country.json";
        const pElement = document.createElement("p");

        // Define the properties and data for the API request
        const requestOptions = {
            method: "GET",
        }

        // Send POST request to API, get response and set the reponse as paragraph element text
        try {
            const response = await (await fetch(API_URL, requestOptions)).json();
            pElement.textContent = response.ip;
           // pElement.textContent = "mock";
        } catch (error) { // Add error class to the paragraph element and set error text
            pElement.textContent = "Oops! Something went wrong while retrieving the response. Please try again.";
        }

        container?.appendChild(pElement)
        container?.scrollTo(-1, container.scrollHeight);
    }
}

declare global {
    interface HTMLElementTagNameMap {
        'donuts-app': DonutsAppElement;
    }
}

customElements.define(DonutsAppElement.is, DonutsAppElement);
