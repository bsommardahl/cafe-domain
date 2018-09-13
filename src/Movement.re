type t = {
  productId: string,
  productChildren: list(Product.child),
  quantity: int,
};

let fromJs = js: t => {
  productId: js##product,
  productChildren:
    switch (Js.Nullable.toOption(js##productChildren)) {
    | Some(products) =>
      products |> Array.to_list |> List.map(x => x |> Product.childFromJs)
    | None => []
    },
  quantity: js##quantity,
};

let toJs = (t: t) => {
  "productId": t.productId,
  "productChildrenIds":
    t.productChildren |> List.map(x => x |> Product.childToJs) |> Array.of_list,
  "quantity": t.quantity,
};