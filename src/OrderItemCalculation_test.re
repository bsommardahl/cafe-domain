open Jest;

open Expect;

open OrderItemCalculation;

let buildOrderItem = (price: int, taxMethod) : OrderItem.t => {
  id: "",
  quantity: 0,
  sku: "t",
  name: "t",
  suggestedPrice: price,
  taxCalculation: taxMethod,
  addedOn: 0.0,
  salePrice: 0,
};

describe("order item calculation", () => {
  describe("when calculating totals for an entire order", () => {
    describe("with several items", () => {
      let orderItems: list(OrderItem.t) = [
        {
          id: "",
          quantity: 1,
          sku: "PizzaPep",
          name: "Pizza Peperoni",
          suggestedPrice: 20000,
          taxCalculation: TotalFirst(15),
          addedOn: 1.1,
          salePrice: 20000,
        },
        {
          id: "",
          quantity: 1,
          sku: "PizzaCheese",
          name: "Pizza Queso",
          suggestedPrice: 20000,
          taxCalculation: TotalFirst(15),
          addedOn: 1.1,
          salePrice: 20000,
        },
        {
          id: "",
          quantity: 1,
          sku: "PizzaAloha",
          name: "Pizza Aloja",
          suggestedPrice: 20000,
          taxCalculation: TotalFirst(15),
          addedOn: 1.1,
          salePrice: 20000,
        },
      ];
      test("the tax and the subtotal should equal the total", () => {
        let totals = orderItems |> OrderItemCalculation.getTotals([]);
        expect(totals.subTotal) |> toEqual(52173) |> ignore;
        expect(totals.tax) |> toEqual(7827) |> ignore;
        expect(totals.subTotal + totals.tax) |> toEqual(totals.total);
      });
    });
    describe("with several items and a discount", () => {
      let orderItems: list(OrderItem.t) = [
        {
          id: "",
          quantity: 1,
          sku: "PizzaPep",
          name: "Pizza Peperoni",
          suggestedPrice: 20000,
          taxCalculation: TotalFirst(15),
          addedOn: 1.1,
          salePrice: 20000,
        },
        {
          id: "",
          quantity: 1,
          sku: "PizzaCheese",
          name: "Pizza Queso",
          suggestedPrice: 20000,
          taxCalculation: SubTotalFirst(15),
          addedOn: 1.1,
          salePrice: 20000,
        },
        {
          id: "",
          quantity: 1,
          sku: "PizzaAloha",
          name: "Pizza Aloja",
          suggestedPrice: 20000,
          taxCalculation: Exempt,
          addedOn: 1.1,
          salePrice: 20000,
        },
      ];
      let totals =
        orderItems
        |> OrderItemCalculation.getTotals([
             {id: "test", name: "test", percent: 10},
           ]);
      test("the discount should be 10% of the subtotal", () =>
        expect(totals.discounts) |> toEqual(6000)
      );
      /**/
      test("the discount should be applied to the subtotal", () =>
        expect(totals.subTotal) |> toEqual(51652)
      );
      /**/
      test("the the tax should be calcualted per item and then rounded", () =>
        expect(totals.tax) |> toEqual(5048)
      );
      /**/
      test("the total should be the sum of all other subtotals", () =>
        expect(totals.total) |> toEqual(56700)
      );
    });
    describe("with one pizza and a discount", () => {
      let orderItems: list(OrderItem.t) = [
        {
          id: "",
          quantity: 1,
          sku: "PizzaCheese",
          name: "Pizza Queso",
          suggestedPrice: 12500,
          taxCalculation: TotalFirst(15),
          addedOn: 1.1,
          salePrice: 0,
        },
      ];
      let totals =
        orderItems
        |> OrderItemCalculation.getTotals([
             {id: "test", name: "test", percent: 25},
           ]);
      test("the discount should be 25% of the subtotal", () =>
        expect(totals.discounts) |> toEqual(3125)
      );
      /**/
      test("the discount should be applied to the subtotal", () =>
        expect(totals.subTotal) |> toEqual(8152)
      );
      /**/
      test("the the tax should be calculated per item and then rounded", () =>
        expect(totals.tax) |> toEqual(1223)
      );
      test("the total should be the sum of all other subtotals", () =>
        expect(totals.total) |> toEqual(9375)
      );
    });
  });
  describe("with weird numbers and two discounts", () => {
    let discount1: Discount.t = {id: "test", name: "test", percent: 33};
    let discount2: Discount.t = {id: "test", name: "test", percent: 25};
    let discounts = [discount1, discount2];
    let price1 = 541234123412355;
    let price2 = 42234242342423;
    let price3 = 76575686755676;
    let orderItem1 = buildOrderItem(price1, TotalFirst(123));
    let orderItem2 = buildOrderItem(price2, SubTotalFirst(187));
    let orderItem3 = buildOrderItem(price3, Exempt);
    let orderItems: list(OrderItem.t) = [orderItem1, orderItem2, orderItem3];
    let expectedTotals: list(OrderItemCalculation.orderItemTotals) = [
      OrderItemCalculation.totalFirstCalculator(123, discounts, orderItem1),
      OrderItemCalculation.subTotalFirstCalculator(
        187,
        discounts,
        orderItem2,
      ),
      OrderItemCalculation.exemptCalculator(0, discounts, orderItem3),
    ];
    let discount =
      Belt.List.reduce(expectedTotals, 0.0, (acc, tot) =>
        acc +. tot.discounts *. 100.
      )
      |> Js.Math.round
      |> int_of_float;
    let subTotal =
      Belt.List.reduce(expectedTotals, 0.0, (acc, tot) =>
        acc +. tot.subTotal *. 100.
      )
      |> Js.Math.round
      |> int_of_float;
    let taxes =
      Belt.List.reduce(expectedTotals, 0.0, (acc, tot) =>
        acc +. tot.tax *. 100.
      )
      |> Js.Math.round
      |> int_of_float;
    let totals = orderItems |> OrderItemCalculation.getTotals(discounts);
    test("the discount should be 16% of the subtotal", () =>
      expect(totals.discounts) |> toEqual(discount)
    );
    test("the subtotal should be the sum of the discounted subtotals", () =>
      expect(totals.subTotal) |> toEqual(subTotal)
    );
    test("the the tax should be equal the sum of thr tax for each item", () =>
      expect(totals.tax) |> toEqual(taxes)
    );
    test("the total should be the sum of all other subtotals", () =>
      expect(totals.total) |> toEqual(subTotal + taxes)
    );
  });
  describe("when calculating order item totals", () => {
    describe("when exempt tax calculation", () => {
      describe("and with a discount", () => {
        let orderItem: OrderItem.t = {
          id: "",
          quantity: 1,
          sku: "some",
          name: "some",
          suggestedPrice: 1000,
          addedOn: 0.0,
          salePrice: 1000,
          taxCalculation: Tax.Exempt,
        };
        let totals =
          exemptCalculator(
            0,
            [{id: "id", name: "name", percent: 10}],
            orderItem,
          );
        /**/
        test("the subtotal should be 900", () =>
          expect(totals.subTotal) |> toEqual(9.)
        );
        test("the total should be equal to the subtotal", () =>
          expect(totals.subTotal) |> toEqual(totals.total)
        );
        test("it should have a 100 lemp discount", () =>
          expect(totals.discounts) |> toEqual(1.)
        );
        test("it should return zero tax", () =>
          expect(totals.tax) |> toEqual(0.)
        );
      });
      describe("and with no discounts", () => {
        let orderItem: OrderItem.t = {
          id: "",
          quantity: 1,
          sku: "some",
          name: "some",
          suggestedPrice: 100,
          addedOn: 0.0,
          salePrice: 100,
          taxCalculation: Tax.Exempt,
        };
        let totals = exemptCalculator(0, [], orderItem);
        /**/
        test("the subtotal should be the sale price", () =>
          expect(totals.subTotal) |> toEqual(1.)
        );
        /**/
        test("the total should be equal to the subtotal", () =>
          expect(totals.total) |> toEqual(1.)
        );
        test("it should have a 0 discount", () =>
          expect(totals.discounts) |> toEqual(0.)
        );
        test("it should return zero tax", () =>
          expect(totals.tax) |> toEqual(0.)
        );
      });
    });
    describe("with total first tax calculation", () => {
      describe("and no discount", () => {
        let orderItem: OrderItem.t = {
          id: "",
          quantity: 1,
          sku: "some",
          name: "some",
          suggestedPrice: 100,
          addedOn: 0.0,
          salePrice: 100,
          taxCalculation: Tax.TotalFirst(15),
        };
        let totals = totalFirstCalculator(15, [], orderItem);
        test("the total should the suggested price", () =>
          expect(totals.total) |> toEqual(1.)
        );
        /**/
        test("the tax should be inverted from total", () =>
          expect(totals.tax) |> toEqual(0.13043478260869557)
        );
        /**/
        test("the subtotal derrived from the total minus the tax amount", () =>
          expect(totals.subTotal) |> toEqual(0.8695652173913044)
        );
        test("it should not have a discount", () =>
          expect(totals.discounts) |> toEqual(0.)
        );
      });
      describe("and no discount and quantity more than one", () => {
        let orderItem: OrderItem.t = {
          id: "",
          quantity: 4,
          sku: "some",
          name: "some",
          suggestedPrice: 100,
          addedOn: 0.0,
          salePrice: 100,
          taxCalculation: Tax.TotalFirst(15),
        };
        let totals = totalFirstCalculator(15, [], orderItem);
        test("the total should be the suggested price", () =>
          expect(totals.total) |> toEqual(4.)
        );
        /**/
        test("the tax should be inverted from total", () =>
          expect(totals.tax) |> toEqual(0.5217391304347823)
        );
        /**/
        test("the subtotal derived from the total minus the tax amount", () =>
          expect(totals.subTotal) |> toEqual(3.4782608695652177)
        );
        test("it should not have a discount", () =>
          expect(totals.discounts) |> toEqual(0.)
        );
      });
      describe("and with a low discount", () => {
        let orderItem: OrderItem.t = {
          id: "",
          quantity: 1,
          sku: "some",
          name: "some",
          suggestedPrice: 1100,
          addedOn: 0.0,
          salePrice: 0,
          taxCalculation: Tax.TotalFirst(15),
        };
        let totals =
          totalFirstCalculator(
            15,
            [{id: "id", name: "name", percent: 10}],
            orderItem,
          );
        test(
          /**/ "the subtotal should be discounted and derived from the total",
          () =>
          expect(totals.subTotal) |> toEqual(8.608695652173914)
        );
        test("the total should be the discounted suggested price", () =>
          expect(totals.total) |> toEqual(9.9)
        );
        test("it should have a discount", () =>
          expect(totals.discounts) |> toEqual(1.1)
        );
        /**/
        test("it should return tax", () =>
          expect(totals.tax) |> toEqual(1.2913043478260864)
        );
      });
      describe("and with a 100% discount", () => {
        let orderItem: OrderItem.t = {
          id: "",
          quantity: 1,
          sku: "some",
          name: "free",
          suggestedPrice: 1000,
          addedOn: 0.0,
          salePrice: 0,
          taxCalculation: Tax.TotalFirst(15),
        };
        let totals =
          totalFirstCalculator(
            15,
            [{id: "id", name: "name", percent: 100}],
            orderItem,
          );
        test("the subtotal should be zero", () =>
          expect(totals.subTotal) |> toEqual(0.)
        );
        test("the total should be zero", () =>
          expect(totals.total) |> toEqual(0.)
        );
        test("the discount should be the same as the suggested price", () =>
          expect(totals.discounts) |> toEqual(10.)
        );
        test("the tax should be zero", () =>
          expect(totals.tax) |> toEqual(0.)
        );
      });
    });
    describe("and with a 95% discount", () => {
      let orderItem: OrderItem.t = {
        id: "",
        quantity: 1,
        sku: "some",
        name: "almost free",
        suggestedPrice: 10000,
        addedOn: 0.0,
        salePrice: 0,
        taxCalculation: Tax.TotalFirst(15),
      };
      let totals =
        totalFirstCalculator(
          15,
          [{id: "id", name: "name", percent: 95}],
          orderItem,
        );
      /**/
      test("the subtotal should be less than the total", () =>
        expect(totals.subTotal) |> toEqual(4.347826086956522)
      );
      test("the total should be only 5% of the original sales price", () =>
        expect(totals.total) |> toEqual(5.)
      );
      test("the discount should be 95%", () =>
        expect(totals.discounts) |> toEqual(95.)
      );
      /**/
      test("the tax should be from the 5% subtotal", () =>
        expect(totals.tax) |> toEqual(0.6521739130434776)
      );
    });
    describe("when discounting back down to normal price", () => {
      let orderItem: OrderItem.t = {
        id: "",
        quantity: 1,
        sku: "some",
        name: "local discount target",
        suggestedPrice: 130,
        addedOn: 0.0,
        salePrice: 0,
        taxCalculation: Tax.TotalFirst(15),
      };
      let totals =
        totalFirstCalculator(
          15,
          [{id: "id", name: "name", percent: 25}],
          orderItem,
        );
      test("the total should be the normal price", () =>
        expect(totals.total) |> toEqual(0.9750000000000001)
      );
    });
    describe("with subtotal first tax calculation", () => {
      describe("with no discount", () => {
        let orderItem: OrderItem.t = {
          id: "",
          quantity: 1,
          sku: "some",
          name: "some",
          suggestedPrice: 100,
          addedOn: 0.0,
          salePrice: 100,
          taxCalculation: Tax.TotalFirst(15),
        };
        let totals = subTotalFirstCalculator(15, [], orderItem);
        /**/
        test("the subtotal should be the suggested price", () =>
          expect(totals.subTotal) |> toEqual(1.)
        );
        /**/
        test("the tax should be multiplied from the subtotal", () =>
          expect(totals.tax) |> toEqual(0.15)
        );
        /**/
        test("the total should the sum of the subtotal and the tax", () =>
          expect(totals.total) |> toEqual(1.15)
        );
        test("it should not have a discount", () =>
          expect(totals.discounts) |> toEqual(0.)
        );
      });
      describe("with one discount", () => {
        let orderItem: OrderItem.t = {
          id: "",
          quantity: 1,
          sku: "some",
          name: "some",
          suggestedPrice: 1036,
          addedOn: 0.0,
          salePrice: 0,
          taxCalculation: Tax.TotalFirst(15),
        };
        let totals =
          subTotalFirstCalculator(
            15,
            [{id: "id", name: "name", percent: 10}],
            orderItem,
          );
        /**/
        test("the subtotal should be the discounted suggested price", () =>
          expect(totals.subTotal) |> toEqual(9.324)
        );
        /**/
        test("the total should be equal the subtotal + tax", () =>
          expect(totals.total) |> toEqual(10.7226)
        );
        test("it should have a discount", () =>
          expect(totals.discounts) |> toEqual(1.036)
        );
        /**/
        test("it should return tax", () =>
          expect(totals.tax) |> toEqual(1.3985999999999998)
        );
      });
    });
  });
});