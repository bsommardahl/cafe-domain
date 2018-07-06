type t = {
  sku: string,
  productName: string,
  taxRate: Percent.t,
  salePrice: Money.t,
  quantity: int,
  subTotal: Money.t,
  tax: Money.t,
  total: Money.t,
};

let fromSalesList = (sales: list(Sale.t)) : list(t) =>
  sales
  |> Group.by((x: Sale.t) =>
       x.sku ++ string_of_int(x.salePrice) ++ string_of_int(x.taxRate)
     )
  |> List.map((x: Group.group(Sale.t)) => {
       let sub =
         x.value
         |. Belt.List.reduce(0, (acc, cur) =>
              acc + cur.salePrice * cur.quantity
            );
       let tax =
         x.value
         |. Belt.List.reduce(0, (acc, cur) =>
              acc
              + (cur.salePrice |> Percent.calculate(cur.taxRate))
              * cur.quantity
            );
       let total = sub + tax;
       let sales = x.value;
       let firstSale = (sales |> Array.of_list)[0];
       {
         sku: firstSale.sku,
         productName: firstSale.productName,
         taxRate: firstSale.taxRate,
         salePrice: firstSale.salePrice,
         subTotal: sub,
         tax,
         total,
         quantity:
           sales
           |. Belt.List.reduce(0, (quantity, sale) =>
                quantity + sale.quantity
              ),
       };
     });

let sum = (whatToSum: t => int, l: list(t)) =>
  l |. Belt.List.reduce(0, (a, c) => a + whatToSum(c));