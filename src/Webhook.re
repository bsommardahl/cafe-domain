module EventType = {
  type t =
    | BeforeOrderPaid
    | OrderPaid
    | OrderReturned
    | ReprintReceipt
    | PrintOrder
    | PrintProduct
    | AfterProductCreated
    | Error
    | Unrecognized;
  let toString = e =>
    switch (e) {
    | OrderPaid => "OrderPaid"
    | BeforeOrderPaid => "BeforeOrderPaid"
    | OrderReturned => "OrderReturned"
    | ReprintReceipt => "ReprintReceipt"
    | PrintOrder => "PrintOrder"
    | PrintProduct => "PrintProduct"
    | AfterProductCreated => "AfterProductCreated"
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
    | "PrintProduct" => PrintProduct
    | "AfterProductCreated" => AfterProductCreated
    | "Error" => Error
    | _ => Unrecognized
    };
};

module EventSource = {
  type t =
    | Order
    | Product
    | Unrecognized;
  let toString = s =>
    switch (s) {
    | Order => "Order"
    | Product => "Product"
    | Unrecognized => "Unrecognized"
    };
  let toT = (s: string) =>
    switch (s) {
    | "Order" => Order
    | "Product" => Product
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
    | AwaitResponse => "AwaitResponse"
    };
  let fromString = s =>
    switch (s) {
    | "AwaitResponse" => AwaitResponse
    | _ => FireAndForget
    };
};

module PayloadType = {
  type t =
    | Json
    | Text;

  let toString = p =>
    switch (p) {
    | Json => "application/json"
    | Text => "text/plain"
    };

  let fromString = p =>
    switch (p) {
    | "text/plain" => Text
    | "application/json"
    | _ => Json
    };
};

type t = {
  id: string,
  name: string,
  source: EventSource.t,
  url: string,
  event: EventType.t,
  behavior: Behavior.t,
  payload: PayloadType.t,
};

module New = {
  type t = {
    name: string,
    url: string,
    event: EventType.t,
    source: EventSource.t,
    behavior: Behavior.t,
    payload: PayloadType.t,
  };
  let toJs = (webhook: t) => {
    "name": webhook.name,
    "url": webhook.url,
    "event": webhook.event |> EventType.toString,
    "source": webhook.source |> EventSource.toString,
    "behavior": webhook.behavior |> Behavior.toString,
    "payload": webhook.payload |> PayloadType.toString,
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
  "payload": string,
};

let fromJs = webhookJs: t => {
  id: webhookJs##_id,
  name: webhookJs##name,
  url: webhookJs##url,
  event: webhookJs##event |> EventType.toT,
  source: webhookJs##source |> EventSource.toT,
  behavior: webhookJs##behavior |> Behavior.fromString,
  payload: webhookJs##payload |> PayloadType.fromString,
};

let toJsWithRev = (id: string, rev: option(string), webhook: t) => {
  "_id": id,
  "_rev": Js.Nullable.return(rev),
  "name": webhook.name,
  "url": webhook.url,
  "event": webhook.event |> EventType.toString,
  "source": webhook.source |> EventSource.toString,
  "behavior": webhook.behavior |> Behavior.toString,
  "payload": webhook.payload |> PayloadType.toString,
};

let toJs = (webhook: t): jsT => {
  "_id": webhook.id,
  "name": webhook.name,
  "url": webhook.url,
  "event": webhook.event |> EventType.toString,
  "source": webhook.source |> EventSource.toString,
  "behavior": webhook.behavior |> Behavior.toString,
  "payload": webhook.payload |> PayloadType.toString,
};