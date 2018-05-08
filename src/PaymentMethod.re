[@bs.deriving jsConverter]
type t = {
  name: string,
  hasExternalId: bool,
};

let default = {name: "paymentMethod.cash", hasExternalId: false};

let toJs = tToJs;

let fromJs = tFromJs;

let tempAllPaymentMethods = [
  default,
  {name: "paymentMethod.card", hasExternalId: true},
];