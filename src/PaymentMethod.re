type t = {
  name: string,
  hasExternalId: bool,
};

let default = {name: "paymentMethod.cash", hasExternalId: false};

let toJs = t : Js.Nullable.t('a) =>
  Js.Nullable.return({"name": t.name, "hasExternalId": t.hasExternalId});

let fromJs = (t: Js.Nullable.t('a)) =>
  switch (Js.Null_undefined.toOption(t)) {
  | None => default
  | Some(js) => {name: js##name, hasExternalId: js##hasExternalId}
  };

let tempAllPaymentMethods = [
  default,
  {name: "paymentMethod.card", hasExternalId: true},
];