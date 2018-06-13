type t = {
  product: Product.t,
  quantity: int,
};

let fromJs = js : t => {
  product: js##product |> Product.mapFromJs,
  quantity: js##quantity,
};

let toJs = (t: t) => {
  "product": t.product |> Product.mapToJs,
  "quantity": t.quantity,
};