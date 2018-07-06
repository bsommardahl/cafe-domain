open Jest;

open Expect;

let buildSale = (sku, price, taxRate, quantity) : Sale.t => {
  sku,
  productName: "test",
  taxRate,
  salePrice: price,
  suggestedPrice: 0,
  quantity,
  discounts: [],
};

describe("The product group module", () =>
  describe("when converting a list of sales to a grouped list products", () => {
    describe("where items are normal sales", () => {
      let bread = buildSale("bread", 100, 15, 2);
      let cheese = buildSale("cheese", 100, 15, 1);
      let sales = [bread, bread, bread, cheese, cheese];
      let groupedSales = ProductGroup.fromSalesList(sales);
      test("it should calculate the subtotal of all items", () =>
        expect(groupedSales)
        |> toEqual(
             ProductGroup.[
               {
                 sku: bread.sku,
                 productName: bread.productName,
                 taxRate: bread.taxRate,
                 salePrice: bread.salePrice,
                 quantity: 6,
                 subTotal: 600,
                 tax: 90,
                 total: 690,
               },
               {
                 sku: cheese.sku,
                 productName: cheese.productName,
                 taxRate: cheese.taxRate,
                 salePrice: cheese.salePrice,
                 quantity: 2,
                 subTotal: 200,
                 tax: 30,
                 total: 230,
               },
             ],
           )
      );
    });
    describe("where items have changed price or taxRate", () => {
      let bread1 = buildSale("bread", 1000, 15, 1);
      let bread2 = buildSale("bread", 1000, 10, 1);
      let cheese1 = buildSale("cheese", 500, 15, 1);
      let cheese2 = buildSale("cheese", 1000, 15, 1);
      let sales = [
        bread1,
        bread1,
        bread1,
        cheese2,
        cheese2,
        cheese1,
        cheese1,
        bread2,
        bread2,
      ];
      let groupedSales = ProductGroup.fromSalesList(sales);
      test("it should calculate the subtotal of all items", () =>
        expect(groupedSales)
        |> toEqual(
             ProductGroup.[
               {
                 sku: bread1.sku,
                 productName: bread1.productName,
                 taxRate: bread1.taxRate,
                 salePrice: bread1.salePrice,
                 quantity: 3,
                 subTotal: 3000,
                 tax: 450,
                 total: 3450,
               },
               {
                 sku: cheese2.sku,
                 productName: cheese2.productName,
                 taxRate: cheese2.taxRate,
                 salePrice: cheese2.salePrice,
                 quantity: 2,
                 subTotal: 2000,
                 tax: 300,
                 total: 2300,
               },
               {
                 sku: cheese1.sku,
                 productName: cheese1.productName,
                 taxRate: cheese1.taxRate,
                 salePrice: cheese1.salePrice,
                 quantity: 2,
                 subTotal: 1000,
                 tax: 150,
                 total: 1150,
               },
               {
                 sku: bread2.sku,
                 productName: bread2.productName,
                 taxRate: bread2.taxRate,
                 salePrice: bread2.salePrice,
                 quantity: 2,
                 subTotal: 2000,
                 tax: 200,
                 total: 2200,
               },
             ],
           )
      );
    });
  })
);