open Jest;

open Expect;

let buildOrderItem = (name: string, suggestedPrice: int) : OrderItem.t => {
  id: "",
  quantity: 0,
  notes: [],
  sku: "test",
  name,
  suggestedPrice,
  addedOn: 0.0,
  salePrice: 0,
  taxCalculation: Tax.SubTotalFirst(15),
};

let buildOrder = (items, discounts) : Order.t => {
  id: "test",
  customerName: "test",
  orderItems: items,
  paid:
    Some({
      on: 0.0,
      by: "test",
      discount: 0,
      subTotal: 0,
      tax: 0,
      total: 0,
      externalId: "",
      method: PaymentMethod.default,
    }),
  returned: None,
  createdOn: 0.0,
  discounts,
  lastUpdated: None,
  removed: false,
  meta: None,
};

let buildDiscount = (name: string, percent: Percent.t) : Discount.t => {
  id: name,
  name,
  percent,
};

let discount10 = buildDiscount("test1", 10);

let discount15 = buildDiscount("test2", 15);

let bread = buildOrderItem("bread", 10000);

let cheese = buildOrderItem("cheese", 5000);

let drink = buildOrderItem("drink", 2000);

describe("The discount group functions", () =>
  describe("when converting a list of orders to a list of discounts", () => {
    describe("where the order has one discount", () => {
      let order = buildOrder([cheese, bread, drink], [discount10]);
      let discounts = order |> DiscountGroup.fromOrder;
      test(
        "it should aggregate the discounts from the orders into one group", () =>
        expect(discounts)
        |> toEqual(
             DiscountGroup.[
               {id: "test1", name: "test1", percent: 10, amount: 1700},
             ],
           )
      );
    });
    describe("where the order has two discounts", () => {
      let orders = [
        buildOrder([cheese, bread, drink], [discount10, discount10]),
      ];
      let discounts = orders |> DiscountGroup.fromOrders;
      test(
        "it should aggregate the discounts from the orders into one group", () =>
        expect(discounts)
        |> toEqual(
             DiscountGroup.[
               {id: "test1", name: "test1", percent: 10, amount: 3400},
             ],
           )
      );
    });
    describe("where the order has various discounts", () => {
      let orders = [
        buildOrder(
          [cheese, bread, drink],
          [discount10, discount10, discount15],
        ),
      ];
      let discounts = orders |> DiscountGroup.fromOrders;
      test(
        "it should aggregate the discounts from the orders into one group", () =>
        expect(discounts)
        |> toEqual(
             DiscountGroup.[
               {id: "test1", name: "test1", percent: 10, amount: 3400},
               {id: "test2", name: "test2", percent: 15, amount: 2550},
             ],
           )
      );
    });
  })
);