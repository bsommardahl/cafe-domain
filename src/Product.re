[@bs.deriving jsConverter]
type child = {
  quantity: int,
  productId: string,
};
[@bs.deriving jsConverter]
type t = {
  id: string,
  sku: string,
  name: string,
  tags: list(string),
  department: string,
  location: string,
  weight: int,
  startDate: option(Date.t),
  endDate: option(Date.t),
  suggestedPrice: int,
  onHand: int,
  unit: string,
  taxCalculation: Tax.taxCalculationMethod,
  products: list(child),
};

let fromOptionalDate = d =>
  switch (d) {
  | None => 0.0
  | Some(date) => date
  };
let toOptionalDate = d => Js.Nullable.toOption(d);

module NewProduct = {
  [@bs.deriving jsConverter]
  type t = {
    sku: string,
    name: string,
    tags: list(string),
    onHand: int,
    department: string,
    weight: int,
    location: string,
    startDate: option(Date.t),
    endDate: option(Date.t),
    suggestedPrice: int,
    unit: string,
    taxCalculation: Tax.taxCalculationMethod,
    products: list(child),
  };
  let mapToJs = (prod: t) => {
    "sku": prod.sku,
    "name": prod.name,
    "suggestedPrice": prod.suggestedPrice,
    "onHand": prod.onHand,
    "department": prod.department,
    "weight": prod.weight,
    "location": prod.location,
    "unit": prod.unit,
    "startDate": fromOptionalDate(prod.startDate),
    "endDate": fromOptionalDate(prod.endDate),
    "tags": prod.tags |> Array.of_list,
    "taxCalculation": prod.taxCalculation |> Tax.Calculation.toDelimitedString,
    "products":
      prod.products |> List.map(x => x |> childToJs) |> Array.of_list,
  };
};

let mapFromJs = prodJs : t => {
  id: prodJs##_id,
  sku: prodJs##sku,
  name: prodJs##name,
  suggestedPrice: prodJs##suggestedPrice,
  tags: prodJs##tags,
  products:
    switch (Js.Nullable.toOption(prodJs##products)) {
    | Some(products) =>
      products |> Array.to_list |> List.map(x => x |> childFromJs)
    | None => []
    },
  onHand: prodJs##onHand,
  department: prodJs##department,
  weight: prodJs##weight,
  location: prodJs##location,
  unit: prodJs##unit,
  startDate: toOptionalDate(prodJs##startDate),
  endDate: toOptionalDate(prodJs##endDate),
  taxCalculation: prodJs##taxCalculation |> Tax.Calculation.toMethod,
};

let mapToJsWithRev = (id: string, rev: option(string), prod: t) => {
  "_id": id,
  "_rev": Js.Nullable.return(rev),
  "sku": prod.sku,
  "name": prod.name,
  "suggestedPrice": prod.suggestedPrice,
  "tags": prod.tags,
  "products": prod.products |> List.map(x => x |> childToJs) |> Array.of_list,
  "onHand": prod.onHand,
  "startDate": prod.startDate |> fromOptionalDate,
  "endDate": fromOptionalDate(prod.endDate),
  "department": prod.department,
  "weight": prod.weight,
  "location": prod.location,
  "unit": prod.unit,
  "taxCalculation": prod.taxCalculation |> Tax.Calculation.toDelimitedString,
};

let mapToJs = (prod: t) => prod |> mapToJsWithRev(prod.id, None);

let getTags = (products: list(t)) : list(string) => {
  let tagArrArr = products |> List.map(p => p.tags);
  let allTags = tagArrArr |> List.flatten;
  let uniqueTags =
    allTags |> List.sort_uniq((tag1, tag2) => String.compare(tag1, tag2));
  uniqueTags;
};

let filterProducts = (tag: string, products: list(t)) : list(t) =>
  products |> List.filter(p => p.tags |> List.exists(t => t === tag));