type t = {
  id: string,
  quantity: int,
  notes: list(OrderItemNote.t),
  sku: string,
  name: string,
  suggestedPrice: Money.t,
  addedOn: float,
  salePrice: Money.t,
  taxCalculation: Tax.taxCalculationMethod,
};

let mapOrderItemFromJs = itemJs : t => {
  id: itemJs##id,
  quantity:
    switch (Js.Null_undefined.toOption(itemJs##quantity)) {
    | Some(quantity) => quantity
    | None => 1
    },
  notes:
    switch (Js.Null_undefined.toOption(itemJs##notes)) {
    | Some(orderItemNotes) =>
      orderItemNotes
      |> Array.map(i => OrderItemNote.mapOrderItemNoteFromJs(i))
      |> Array.to_list
    | None => []
    },
  sku: itemJs##sku,
  name: itemJs##name,
  suggestedPrice: itemJs##suggestedPrice,
  addedOn: JsUtils.convertDate(itemJs##addedOn),
  salePrice: itemJs##salePrice,
  taxCalculation: itemJs##taxCalculation |> Tax.Calculation.toMethod,
};

let orderItemToJs = (orderItem: t) => {
  "id": orderItem.id,
  "quantity": orderItem.quantity,
  "notes": orderItem.notes,
  "sku": orderItem.sku,
  "name": orderItem.name,
  "suggestedPrice": orderItem.suggestedPrice,
  "addedOn": orderItem.addedOn,
  "salePrice": orderItem.salePrice,
  "taxCalculation":
    orderItem.taxCalculation |> Tax.Calculation.toDelimitedString,
};