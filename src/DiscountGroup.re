type t = {
  id: string,
  name: string,
  percent: Percent.t,
  amount: Money.t,
};

let sum = (whatToSum: t => int, l: list(t)) =>
  l |. Belt.List.reduce(0, (a, c) => a + whatToSum(c));

let fromOrder = (order: Order.t) : list(t) =>
  order.discounts
  |> List.map((d: Discount.t) => {
       let amount =
         order.orderItems
         |. Belt.List.reduce(0, (a, i) => a + i.suggestedPrice)
         |> Percent.calculate(d.percent);
       {id: d.id, name: d.name, percent: d.percent, amount};
     });

let fromOrders = (orders: list(Order.t)) =>
  orders
  |> List.map(fromOrder)
  |> List.concat
  |> Group.by((d: t) => d.id)
  |> List.map((g: Group.group(t)) =>
       {
         id: g.key,
         name: List.nth(g.value, 0).name,
         percent: List.nth(g.value, 0).percent,
         amount: g.value |. Belt.List.reduce(0, (a, d) => a + d.amount),
       }
     );