module EventType = {
  type t =
    | BeforeOrderPaid
    | OrderPaid
    | OrderReturned
    | ReprintReceipt
    | PrintOrder
    | Error
    | Unrecognized;
  let toString = e =>
    switch (e) {
    | OrderPaid => "OrderPaid"
    | BeforeOrderPaid => "BeforeOrderPaid"
    | OrderReturned => "OrderReturned"
    | ReprintReceipt => "ReprintReceipt"
    | PrintOrder => "PrintOrder"
    | Error => "Error"
    | Unrecognized => "Unrecognized"
    };
  let toT = e =>
    switch (e) {
    | "OrderPaid" => OrderPaid
    | "BeforeOrderPaid" => BeforeOrderPaid
    | "OrderReturned" => OrderReturned
    | "ReprintReceipt" => ReprintReceipt
    | "PrintOrder" => PrintOrder
    | "Error" => Error
    | _ => Unrecognized
    };
};

module EventSource = {
  type t =
    | Order
    | Unrecognized;
  let toString = s =>
    switch (s) {
    | Order => "Order"
    | Unrecognized => "Unrecognized"
    };
  let toT = (s: string) =>
    switch (s) {
    | "Order" => Order
    | _ => Unrecognized
    };
};

type t = {
  id: string,
  name: string,
  source: EventSource.t,
  url: string,
  event: EventType.t,
  updateSource: bool,
};

module New = {
  type t = {
    name: string,
    url: string,
    event: EventType.t,
    source: EventSource.t,
    updateSource: bool,
  };
  let toJs = (webhook: t) => {
    "name": webhook.name,
    "url": webhook.url,
    "event": webhook.event |> EventType.toString,
    "source": webhook.source |> EventSource.toString,
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
  event: webhookJs##event |> EventType.toT,
  source: webhookJs##source |> EventSource.toT,
  updateSource: webhookJs##updateSource,
};

let toJsWithRev = (id: string, rev: option(string), webhook: t) => {
  "_id": id,
  "_rev": Js.Nullable.return(rev),
  "name": webhook.name,
  "url": webhook.url,
  "event": webhook.event |> EventType.toString,
  "source": webhook.source |> EventSource.toString,
  "updateSource": webhook.updateSource,
};

let toJs = (webhook: t) : jsT => {
  "_id": webhook.id,
  "name": webhook.name,
  "url": webhook.url,
  "event": webhook.event |> EventType.toString,
  "source": webhook.source |> EventSource.toString,
  "updateSource": webhook.updateSource,
};