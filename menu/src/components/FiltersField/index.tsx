import React from "react";
import { useProvidableState } from "@components/utils";
import { Filter } from "./Filter";
import { useStyles } from "./styles";

export type FiltersFieldProps = {
  label?: string;
  helperText?: string;
  filters?: string[];
  values?: string[];
  onChange?: (v: string[]) => void;
  marginTop?: number;
};
export const FiltersField: React.FC<FiltersFieldProps> = ({
  label = "Filters:",
  helperText,
  filters = ["Value 1", "Value2", "Value3"],
  values: _values,
  onChange: _onChange,
  marginTop = 20,
}) => {
  const classes = useStyles();

  const [values, onChange] = useProvidableState([], _values, _onChange);

  const filtersItems = React.useMemo(
    () =>
      filters.map((filter) => (
        <Filter
          filter={filter}
          checked={values.includes(filter)}
          values={values}
          onChange={onChange}
        />
      )),
    [values, onChange]
  );

  return (
    <div className={classes.container} style={{ marginTop }}>
      <h5 className={classes.label}>{label}</h5>
      {helperText && <p className={classes.helperText}>{helperText}</p>}
      <div className={classes.filters}>{filtersItems}</div>
    </div>
  );
};
