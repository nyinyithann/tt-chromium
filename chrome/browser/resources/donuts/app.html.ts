import {html} from '//resources/lit/v3_0/lit.rollup.js';
import type {DonutsAppElement} from './app.js';

export function getHtml(this: DonutsAppElement) {
    return html`
<h6>Mojom test</h6>
<div id="example-div">${this.message_}</div>
<div>
    <cr-button @click="${this.checkNumberOfDonuts}">Check</cr-button>
</div>
<div>
    <cr-button @click="${() => this.bakeDonuts(11)}">Bake</cr-button>
</div>`;
}
