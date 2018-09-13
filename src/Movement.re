type t = {
  productId: string,
  quantity: int,
};

let fromJs = js: t => {productId: js##product, quantity: js##quantity};

let toJs = (t: t) => {"productId": t.productId, "quantity": t.quantity};