type t = {
  id: int,
  quantity: int,
  sku: string,
  name: string,
  suggestedPrice: Money.t,
  addedOn: float,
  salePrice: Money.t,
  taxCalculation: Tax.taxCalculationMethod,
};

let mapOrderItemFromJs = itemJs : t => {
  id: itemJs##id,
  quantity: itemJs##quantity,
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
  "sku": orderItem.sku,
  "name": orderItem.name,
  "suggestedPrice": orderItem.suggestedPrice,
  "addedOn": orderItem.addedOn,
  "salePrice": orderItem.salePrice,
  "taxCalculation":
    orderItem.taxCalculation |> Tax.Calculation.toDelimitedString,
};