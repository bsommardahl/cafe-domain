type t = {
  name: string,
  hasExternalId: bool,
};

let toJs = t => {"name": t.name, "hasExternalId": t.hasExternalId};

let fromJs = t => {name: t##name, hasExternalId: t##hasExternalId};

let default = {name: "cash", hasExternalId: false};

let tempAllPaymentMethods = [default, {name: "card", hasExternalId: true}];