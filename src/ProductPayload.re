type t = {
  product: Product.t,
  child: option(Product.t),
};

let fromOptionalProduct = product =>
  switch (product) {
  | Some(product) => Js.Nullable.return(product |> Product.mapToJs)
  | None => Js.Nullable.null
  };

let mapToJs = payload => {
  "product": payload.product |> Product.mapToJs,
  "child": fromOptionalProduct(payload.child),
};