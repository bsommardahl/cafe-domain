type t = {
  productId: string,
  quantity: int,
};

let fromJs = js : t => {productId: js##productId, quantity: js##quantity};

let toJs = (child: t) => {
  "productId": child.productId,
  "quantity": child.quantity,
};