using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace SCPSInventory.Models
{
    public class Inventory
    {
        [Display(Name = "Inventory ID")]
        public int InventoryId { get; set; }
        [Display(Name = "Cost Center ID")]
        public string ccId { get; set; }
        [Display(Name = "Start Date")]
        public DateTime InventoryStartDate { get; set; }
        [Display(Name = "End Date")]
        public DateTime InventoryEndDate { get; set; }
        public InventoryStatus Status { get; set; }
        [Display(Name = "Total Assets")]
        public int numAssetsToInventory { get; set; }
        [Display(Name = "Assets Inventoried")]
        public int numAssetsInventoried { get; set; }
        public List<Asset> AssetList { get; set; }
    }

    public enum InventoryStatus { InProgress, Closed }
}