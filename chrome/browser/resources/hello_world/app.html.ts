import {html} from '//resources/lit/v3_0/lit.rollup.js';
import type {HelloWorldAppElement} from './app.js';

export function getHtml(this: HelloWorldAppElement) {
    return html`
<h1>Hello World</h1>
<div id="example-div">${this.message_}</div>`;
}