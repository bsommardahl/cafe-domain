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

module Behavior = {
  type t =
    | FireAndForget
    | AwaitResponse;
  let toString = b =>
    switch (b) {
    | FireAndForget => "FireAndForget"
    | AwaitResponse => "awaitResponse"
    };
  let fromString = s =>
    switch (s) {
    | "AwaitResponse" => AwaitResponse
    | _ => FireAndForget
    };
};

type t = {
  id: string,
  name: string,
  source: EventSource.t,
  url: string,
  event: EventType.t,
  behavior: Behavior.t,
};

module New = {
  type t = {
    name: string,
    url: string,
    event: EventType.t,
    source: EventSource.t,
    behavior: Behavior.t,
  };
  let toJs = (webhook: t) => {
    "name": webhook.name,
    "url": webhook.url,
    "event": webhook.event |> EventType.toString,
    "source": webhook.source |> EventSource.toString,
    "behavior": webhook.behavior |> Behavior.toString,
  };
};

type jsT = {
  .
  "_id": string,
  "name": string,
  "url": string,
  "event": string,
  "source": string,
  "behavior": string,
};

let fromJs = webhookJs : t => {
  id: webhookJs##_id,
  name: webhookJs##name,
  url: webhookJs##url,
  event: webhookJs##event |> EventType.toT,
  source: webhookJs##source |> EventSource.toT,
  behavior: webhookJs##behavior |> Behavior.fromString,
};

let toJsWithRev = (id: string, rev: option(string), webhook: t) => {
  "_id": id,
  "_rev": Js.Nullable.return(rev),
  "name": webhook.name,
  "url": webhook.url,
  "event": webhook.event |> EventType.toString,
  "source": webhook.source |> EventSource.toString,
  "behavior": webhook.behavior |> Behavior.toString,
};

let toJs = (webhook: t) : jsT => {
  "_id": webhook.id,
  "name": webhook.name,
  "url": webhook.url,
  "event": webhook.event |> EventType.toString,
  "source": webhook.source |> EventSource.toString,
  "behavior": webhook.behavior |> Behavior.toString,
};