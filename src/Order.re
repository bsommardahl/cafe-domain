type t = {
  id: string,
  customerName: string,
  paid: option(Paid.t),
  returned: option(Return.t),
  orderItems: list(OrderItem.t),
  discounts: list(Discount.t),
  createdOn: float,
  lastUpdated: option(float),
  removed: bool,
  meta: Js.Json.t,
};

type updateOrder = {
  id: string,
  customerName: string,
  orderItems: list(OrderItem.t),
  discounts: list(Discount.t),
  returned: option(Return.t),
  paid: option(Paid.t),
  meta: Js.Json.t,
};

type orderVm = {
  id: option(string),
  customerName: string,
  orderItems: list(OrderItem.t),
  discounts: list(Discount.t),
  paid: option(Paid.t),
  returned: option(Return.t),
  createdOn: float,
  lastUpdated: option(float),
  removed: bool,
  meta: Js.Json.t,
};

type newOrder = {
  customerName: string,
  orderItems: list(OrderItem.t),
  discounts: list(Discount.t),
  paid: option(Paid.t),
};

let jsonToString = (json: Js.Json.t) =>
  switch (Js.Json.stringifyAny(json)) {
  | None => "{}"
  | Some(str) => str
  };

let stringToJson = (str: string) : Js.Json.t => Js.Json.parseExn(str);

let mapOrderFromJs = orderJs : t => {
  id: orderJs##_id,
  customerName: orderJs##customerName,
  orderItems:
    switch (Js.Null_undefined.toOption(orderJs##orderItems)) {
    | Some(orderItems) =>
      orderItems
      |> Array.map(i => OrderItem.mapOrderItemFromJs(i))
      |> Array.to_list
    | None => []
    },
  createdOn: JsUtils.convertDate(orderJs##createdOn),
  discounts:
    switch (Js.Nullable.toOption(orderJs##discounts)) {
    | Some(discounts) =>
      discounts |> Array.map(d => d |> Discount.mapFromJs) |> Array.to_list
    | None => []
    },
  paid:
    switch (Js.Null_undefined.toOption(orderJs##paid)) {
    | None => None
    | Some(js) => Some(js |> Paid.fromJs)
    },
  returned:
    switch (Js.Null_undefined.toOption(orderJs##returned)) {
    | None => None
    | Some(js) => Some(js |> Return.fromJs)
    },
  lastUpdated: JsUtils.convertFloatOption(orderJs##lastUpdated),
  meta:
    switch (Js.Null_undefined.toOption(orderJs##meta)) {
    | None => Js.Json.parseExn("{}")
    | Some(js) => js |> stringToJson
    },
  removed: false,
};

let toVm = (o: t) => {
  let vm: orderVm = {
    id:
      switch (o.id) {
      | "" => None
      | id => Some(id)
      },
    customerName: o.customerName,
    orderItems: o.orderItems,
    createdOn: o.createdOn,
    discounts: o.discounts,
    paid: o.paid,
    returned: o.returned,
    lastUpdated: o.lastUpdated,
    meta: o.meta,
    removed: false,
  };
  vm;
};

let vmFromExistingOrder = toVm;

let fromVm = (o: orderVm) : t => {
  id:
    switch (o.id) {
    | None => ""
    | Some(id) => id
    },
  customerName: o.customerName,
  orderItems: o.orderItems,
  createdOn: o.createdOn,
  discounts: o.discounts,
  paid: o.paid,
  returned: o.returned,
  lastUpdated: o.lastUpdated,
  meta: o.meta,
  removed: false,
};

let vmToUpdateOrder = (vm: orderVm) : updateOrder => {
  id:
    switch (vm.id) {
    | None => ""
    | Some(id) => id
    },
  customerName: vm.customerName,
  orderItems: vm.orderItems,
  discounts: vm.discounts,
  paid: vm.paid,
  returned: vm.returned,
  meta: vm.meta,
};

let updateOrderToJs =
    (id: string, rev: string, originalOrder: t, updateOrder: updateOrder) => {
  "_id": id,
  "_rev": rev,
  "orderItems":
    updateOrder.orderItems
    |> List.map(i => OrderItem.orderItemToJs(i))
    |> Array.of_list,
  "customerName": updateOrder.customerName,
  "lastUpdated": Js.Date.now(),
  "discounts":
    updateOrder.discounts
    |> List.map(d => d |> Discount.mapToJs)
    |> Array.of_list,
  "paid":
    switch (updateOrder.paid) {
    | None => Js.Nullable.undefined
    | Some(paid) => Js.Nullable.return(paid |> Paid.toJs)
    },
  "returned":
    switch (updateOrder.returned) {
    | None => Js.Nullable.undefined
    | Some(ret) => Js.Nullable.return(ret |> Return.toJs)
    },
  "meta": originalOrder.meta |> jsonToString,
  "createdOn": originalOrder.createdOn,
};

let toJs = (order: t) => {
  "_id": order.id,
  "orderItems":
    order.orderItems
    |> List.map(i => OrderItem.orderItemToJs(i))
    |> Array.of_list,
  "customerName": order.customerName,
  "lastUpdated": Js.Date.now(),
  "discounts":
    order.discounts |> List.map(d => d |> Discount.mapToJs) |> Array.of_list,
  "paid":
    switch (order.paid) {
    | None => Js.Nullable.undefined
    | Some(paid) => Js.Nullable.return(paid |> Paid.toJs)
    },
  "returned":
    switch (order.returned) {
    | None => Js.Nullable.undefined
    | Some(returned) => Js.Nullable.return(returned |> Return.toJs)
    },
  "meta": order.meta |> jsonToString,
  "createdOn": order.createdOn,
};

let newOrderToJs = (order: newOrder) => {
  "customerName": order.customerName,
  "orderItems":
    order.orderItems
    |> List.map(i => OrderItem.orderItemToJs(i))
    |> Array.of_list,
  "discounts":
    order.discounts |> List.map(d => d |> Discount.mapToJs) |> Array.of_list,
  "createdOn": Date.now(),
  "paid":
    switch (order.paid) {
    | None => Js.Nullable.undefined
    | Some(paid) => Js.Nullable.return(paid |> Paid.toJs)
    },
};