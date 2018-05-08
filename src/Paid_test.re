open Jest;

open Expect;

open OrderItemCalculation;

describe("Paid module", () =>
  describe("when mapping from js", () => {
    describe("with a card method", () => {
      let card: PaymentMethod.t = {name: "card", hasExternalId: true};
      let paid: Paid.t = {
        subTotal: 12300,
        discount: 12300,
        tax: 12300,
        total: 12300,
        on: 412341324.,
        by: "Byron",
        externalId: Some("id"),
        method: card,
      };
      test("he method should still be card", () => {
        let js = paid |> Paid.toJs;
        let p = js |> Paid.fromJs;
        expect(p.method.name) |> toEqual(card.name);
      });
    });
    describe("with cash method", () => {
      let cash: PaymentMethod.t = {name: "cash", hasExternalId: true};
      let paid: Paid.t = {
        subTotal: 12300,
        discount: 12300,
        tax: 12300,
        total: 12300,
        on: 412341324.,
        by: "Byron",
        externalId: Some("id"),
        method: cash,
      };
      test("the method should still be cash", () => {
        let js = paid |> Paid.toJs;
        let p = js |> Paid.fromJs;
        expect(p.method.name) |> toEqual(cash.name);
      });
    });
  })
);