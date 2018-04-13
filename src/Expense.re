module SubTotal = {
  type t = {
    amount: Money.t,
    taxRate: Percent.t,
  };
  let fromJs = js : t => {amount: js##amount, taxRate: js##taxRate};
  let toJs = (item: t) => {"amount": item.amount, "taxRate": item.taxRate};
};

type t = {
  id: string,
  description: string,
  vendor: Vendor.t,
  expenseType: ExpenseType.t,
  date: float,
  subTotals: list(SubTotal.t),
  tax: Money.t,
  total: Money.t,
};

type denormalized = {
  description: string,
  vendor: Vendor.t,
  expenseType: ExpenseType.t,
  date: float,
  subTotal: Money.t,
  taxRate: Percent.t,
  tax: Money.t,
  total: Money.t,
};

let denormalize = (expenses: list(t)) : list(denormalized) =>
  expenses
  |> List.map((e: t) =>
       e.subTotals
       |> List.map((s: SubTotal.t) =>
            {
              description: e.description,
              vendor: e.vendor,
              expenseType: e.expenseType,
              date: e.date,
              subTotal: s.amount,
              taxRate: s.taxRate,
              tax: s.amount |> Percent.calculate(s.taxRate),
              total: (s.amount |> Percent.calculate(s.taxRate)) + s.amount,
            }
          )
     )
  |. List.concat;

let sum = (whatToSum: denormalized => int, l: list(denormalized)) =>
  l |. Belt.List.reduce(0, (a, c) => a + whatToSum(c));

module New = {
  type t = {
    description: string,
    vendor: Vendor.t,
    expenseType: ExpenseType.t,
    date: float,
    subTotals: list(SubTotal.t),
    tax: Money.t,
    total: Money.t,
  };
  let mapToJs = (expense: t) => {
    "description": expense.description,
    "vendor": expense.vendor |> Vendor.toJs,
    "expenseType": expense.expenseType |> ExpenseType.toJs,
    "date": expense.date,
    "subTotals": expense.subTotals |> List.map(s => s |> SubTotal.toJs),
    "tax": expense.tax,
    "total": expense.total,
  };
};

type jsT = {
  .
  "description": string,
  "vendor": Vendor.jsT,
  "expenseType": ExpenseType.jsT,
  "date": float,
  "subTotals": list(SubTotal.t),
  "tax": int,
  "total": int,
};

let fromJs = expenseJs : t => {
  id: expenseJs##_id,
  description: expenseJs##description,
  vendor: expenseJs##vendor |> Vendor.fromJs,
  expenseType: expenseJs##expenseType |> ExpenseType.fromJs,
  date: expenseJs##date,
  subTotals:
    switch (Js.Nullable.toOption(expenseJs##subTotals)) {
    | Some(subTotals) => subTotals |> List.map(s => s |> SubTotal.fromJs)
    | None => []
    },
  tax: expenseJs##tax,
  total: expenseJs##total,
};

let toJs = (expense: t) => {
  "_id": expense.id,
  "description": expense.description,
  "vendor": expense.vendor |> Vendor.toJs,
  "expenseType": expense.expenseType |> ExpenseType.toJs,
  "date": expense.date,
  "subTotals": expense.subTotals |> List.map(s => s |> SubTotal.toJs),
  "tax": expense.tax,
  "total": expense.total,
};

let toJsWithRev = (rev: string, expense: t) => {
  "_id": expense.id,
  "_rev": rev,
  "description": expense.description,
  "vendor": expense.vendor |> Vendor.toJs,
  "expenseType": expense.expenseType |> ExpenseType.toJs,
  "date": expense.date,
  "subTotals": expense.subTotals |> List.map(s => s |> SubTotal.toJs),
  "tax": expense.tax,
  "total": expense.total,
};