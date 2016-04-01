using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Web.Mvc;

namespace SCPSInventory.Models
{
    public class CostCenter
    {
        [Required]
        [RegularExpression("^[0-9]{4}$", ErrorMessage = "Cost Center ID must be a four digit number (0000-9999)")]
        [Remote("validateUniqueCCID", "CostCenters", ErrorMessage = "Cost Center ID Already Exists")]
        [Display(Name = "Cost Center ID")]
        public string CostCenterId { get; set; }
        [Required]
        public string Name { get; set; }
        public List<Inventory> Inventories { get; set; }
        public List<Asset> AssetList { get; set; }
    }
}