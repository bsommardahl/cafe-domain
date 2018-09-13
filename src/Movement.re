type t = {
  productId: string,
  productChildrenIds: list(string),
  quantity: int,
};

let fromJs = js: t => {
  productId: js##product,
  productChildrenIds: js##productChildrenIds |> Array.to_list,
  quantity: js##quantity,
};

let toJs = (t: t) => {
  "productId": t.productId,
  "productChildrenIds": t.productChildrenIds |> Array.of_list,
  "quantity": t.quantity,
};