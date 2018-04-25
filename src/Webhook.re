type source =
  | Order;

let toString = (s: source) =>
  switch (s) {
  | Order => "Order"
  };

let toSource = (s: string) =>
  switch (s) {
  | _ => Order
  };

type t = {
  id: string,
  name: string,
  source,
  url: string,
  event: string,
  updateSource: bool,
};

module New = {
  type t = {
    name: string,
    url: string,
    event: string,
    source,
    updateSource: bool,
  };
  let toJs = (webhook: t) => {
    "name": webhook.name,
    "url": webhook.url,
    "event": webhook.event,
    "source": webhook.source |> toString,
    "updateSource": webhook.updateSource,
  };
};

type jsT = {
  .
  "_id": string,
  "name": string,
  "url": string,
  "event": string,
  "source": string,
  "updateSource": bool,
};

let fromJs = webhookJs : t => {
  id: webhookJs##_id,
  name: webhookJs##name,
  url: webhookJs##url,
  event: webhookJs##event,
  source: webhookJs##source |> toSource,
  updateSource: webhookJs##updateSource,
};

let toJsWithRev = (id: string, rev: option(string), webhook: t) => {
  "_id": id,
  "_rev": Js.Nullable.return(rev),
  "name": webhook.name,
  "url": webhook.url,
  "event": webhook.event,
  "source": webhook.source |> toString,
  "updateSource": webhook.updateSource,
};

let toJs = (webhook: t) : jsT => {
  "_id": webhook.id,
  "name": webhook.name,
  "url": webhook.url,
  "event": webhook.event,
  "source": webhook.source |> toString,
  "updateSource": webhook.updateSource,
};