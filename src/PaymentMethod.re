type t = {
  name: string,
  hasExternalId: bool,
};

let toJs = t => {"name": t.name, "hasExternalId": t.hasExternalId};

let fromJs = t => {name: t##name, hasExternalId: t##hasExternalId};

let default = {name: "paymentMethod.cash", hasExternalId: false};

let tempAllPaymentMethods = [
  default,
  {name: "paymentMethod.card", hasExternalId: true},
];