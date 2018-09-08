module SubTotal = {
  type t = {
    amount: Money.t,
    taxRate: Percent.t,
  };
  let fromJs = js: t => {amount: js##amount, taxRate: js##taxRate};
  let toJs = (item: t) => {"amount": item.amount, "taxRate": item.taxRate};
};

type t = {
  id: string,
  description: string,
  document: string,
  vendor: Vendor.t,
  expenseType: ExpenseType.t,
  date: float,
  subTotals: list(SubTotal.t),
  tax: Money.t,
  total: Money.t,
  movements: list(Movement.t),
  createdBy: string,
};

type denormalized = {
  description: string,
  document: string,
  vendor: Vendor.t,
  expenseType: ExpenseType.t,
  date: float,
  subTotal: Money.t,
  taxRate: Percent.t,
  tax: Money.t,
  total: Money.t,
  createdBy: string,
};

let denormalize = (expenses: list(t)): list(denormalized) =>
  (
    expenses
    |> List.map((e: t) =>
         e.subTotals
         |> List.map((s: SubTotal.t) =>
              {
                description: e.description,
                document: e.document,
                vendor: e.vendor,
                expenseType: e.expenseType,
                date: e.date,
                subTotal: s.amount,
                taxRate: s.taxRate,
                tax: s.amount |> Percent.calculate(s.taxRate),
                total: (s.amount |> Percent.calculate(s.taxRate)) + s.amount,
                createdBy: e.createdBy,
              }
            )
       )
  )
  ->List.concat;

let sum = (whatToSum: denormalized => int, l: list(denormalized)) =>
  l->(Belt.List.reduce(0, (a, c) => a + whatToSum(c)));

module New = {
  type t = {
    description: string,
    document: string,
    vendor: Vendor.t,
    expenseType: ExpenseType.t,
    date: float,
    subTotals: list(SubTotal.t),
    tax: Money.t,
    total: Money.t,
    movements: list(Movement.t),
    createdBy: string,
  };
  let mapToJs = (expense: t) => {
    "description": expense.description,
    "document": expense.document,
    "vendor": expense.vendor |> Vendor.toJs,
    "expenseType": expense.expenseType |> ExpenseType.toJs,
    "date": expense.date,
    "subTotals": expense.subTotals |> List.map(s => s |> SubTotal.toJs),
    "tax": expense.tax,
    "total": expense.total,
    "movements": expense.movements |> List.map(m => m |> Movement.toJs),
    "createdBy": expense.createdBy,
  };
};

type jsT = {
  .
  "description": string,
  "document": string,
  "vendor": Vendor.jsT,
  "expenseType": ExpenseType.jsT,
  "date": float,
  "subTotals": list(SubTotal.t),
  "tax": int,
  "total": int,
  "movements": list(Movement.t),
  "createdBy": string,
};

let fromJs = expenseJs: t => {
  id: expenseJs##_id,
  description: expenseJs##description,
  document: expenseJs##document,
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
  movements:
    switch (Js.Nullable.toOption(expenseJs##movements)) {
    | Some(movements) => movements |> List.map(m => m |> Movement.fromJs)
    | None => []
    },
  createdBy: expenseJs##createdBy,
};

let toJs = (expense: t) => {
  "_id": expense.id,
  "description": expense.description,
  "document": expense.document,
  "vendor": expense.vendor |> Vendor.toJs,
  "expenseType": expense.expenseType |> ExpenseType.toJs,
  "date": expense.date,
  "subTotals": expense.subTotals |> List.map(s => s |> SubTotal.toJs),
  "tax": expense.tax,
  "total": expense.total,
  "movements": expense.movements |> List.map(m => m |> Movement.toJs),
  "createdBy": expense.createdBy,
};

let toJsWithRev = (rev: string, expense: t) => {
  "_id": expense.id,
  "_rev": rev,
  "description": expense.description,
  "document": expense.document,
  "vendor": expense.vendor |> Vendor.toJs,
  "expenseType": expense.expenseType |> ExpenseType.toJs,
  "date": expense.date,
  "subTotals": expense.subTotals |> List.map(s => s |> SubTotal.toJs),
  "tax": expense.tax,
  "total": expense.total,
  "movements": expense.movements |> List.map(m => m |> Movement.toJs),
  "createdBy": expense.createdBy,
};