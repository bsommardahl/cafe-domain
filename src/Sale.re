type t = {
  sku: string,
  salePrice: Money.t,
  productName: string,
  taxRate: Percent.t,
  suggestedPrice: Money.t,
  discounts: list(Discount.t),
};

let listOfSales = (order: Order.t) : list(t) =>
  order.orderItems
  |> List.map((o: OrderItem.t) =>
       {
         sku: o.sku,
         productName: o.name,
         taxRate: o.taxCalculation |> Tax.toTaxRate,
         salePrice: o.salePrice,
         suggestedPrice: o.suggestedPrice,
         discounts: order.discounts,
       }
     );