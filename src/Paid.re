module PaymentMethod = {
  type method =
    | Cash
    | Card;
  let toString = s =>
    switch (s) {
    | Cash => "cash"
    | Card => "card"
    };
  let fromString = p =>
    switch (p) {
    | "card" => Card
    | _ => Cash
    };
};

type t = {
  subTotal: Money.t,
  discount: Money.t,
  tax: Money.t,
  total: Money.t,
  on: Date.t,
  by: string,
  externalId: option(string),
  method: PaymentMethod.method,
};

let toJs = (p: t) => {
  "subTotal": p.subTotal,
  "discount": p.discount,
  "tax": p.tax,
  "total": p.total,
  "on": p.on,
  "by": p.by,
  "externalId": Js.Nullable.fromOption(p.externalId),
  "method": p.method |> PaymentMethod.toString,
};

let fromJs = p => {
  subTotal: p##subTotal,
  discount: p##discount,
  tax: p##tax,
  total: p##total,
  on: p##on,
  by: p##by,
  externalId: Js.Nullable.toOption(p##externalId),
  method: p##method |> PaymentMethod.fromString,
};