type t = {
  name: string,
  hasExternalId: bool,
};

let default = {name: "paymentMethod.cash", hasExternalId: false};

let toJs = t => {"name": t.name, "hasExternalId": t.hasExternalId};

let fromJs = t =>
  switch (Js.Nullable.toOption(t)) {
  | None => default
  | Some(js) => {name: js##name, hasExternalId: js##hasExternalId}
  };

let tempAllPaymentMethods = [
  default,
  {name: "paymentMethod.card", hasExternalId: true},
];